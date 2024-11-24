const { json } = require('express');
const User = require('../Model/users');
const ApiError = require('../error/ApiError');
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');
const fs = require('fs');
const path = require('path');

const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

const generateJwt = (id, email, role) => {
    return jwt.sign({ id, email, role }, process.env.SECRET_KEY, { expiresIn: '24h' });
};

const UsersController = {
    registration: async (req, res, next) => {
        try {
            const { email, password, role = 'USER' } = req.body;
            if (!email || !password) {
                return next(ApiError.badRequest('Некорректный email или пароль'));
            }
            const candidate = await User.getUsersByEmail(email);
            if (candidate) {
                return next(ApiError.badRequest('Пользователь с таким email уже существует'));
            }
    
            if (role !== 'USER' && role !== 'AUTHOR') {
                return next(ApiError.badRequest('Недопустимая роль'));
            }
    
            const hashPassword = await bcrypt.hash(password, 5);
            const user = await User.create(email, hashPassword, role);
            const token = generateJwt(user.ID, user.EMAIL, user.ACCESS_LEVEL);
    
            const avatarPath = path.join(`${__dirname}/../public/static/User${user.ID}.jpg`);
            const defaultAvatarPath = path.join(__dirname, '../public/static/avatar.jpg');
            fs.copyFileSync(defaultAvatarPath, avatarPath);
    
            return res.json({ token, user });
        } catch (error) {
            next(ApiError.badRequest('Ошибка при регистрации'));
        }
    },
    

    login: async (req, res, next) => {
        try {
            const { email, password } = req.body;
            const user = await User.getUsersByEmail(email);
            if (!user) {
                return next(ApiError.internal('Пользователь не найден'));
            }
            const comparePassword = bcrypt.compareSync(password, user.pass);
            if (!comparePassword) {
                return next(ApiError.internal('Указан неверный пароль'));
            }
            const token = generateJwt(user.ID, user.EMAIL, user.ACCESS_LEVEL);
            return res.json({ token, user });
        } catch (error) {
            next(ApiError.badRequest('Ошибка при авторизации'));
        }
    },

    check: async (req, res, next) => {
        try {
            if (!req.user) {
                return next(ApiError.unauthorized('Пользователь не авторизован, не передан user'));
            }
            const token = generateJwt(req.user.id, req.user.email, req.user.role);
            user = await User.getUsersById(req.user.id);
            return res.json({ token, user });
        } catch (error) {
            next(ApiError.badRequest('Ошибка при проверке авторизации'));
        }
    },

    getUsers: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page) || 1;
            const users = await User.getUsers(page);
            res.json(users);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении пользователей'));
        }
    },    

    getUsersById: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const user = await User.getUsersById(id);
            if (user) {
                res.json(user);
            } else {
                next(ApiError.badRequest('Пользователь не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении пользователя'));
        }
    },

    getUserAuthorized: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const user = await User.getUserAuthorized(id);
            if (user) {
                res.json(user);
            } else {
                next(ApiError.badRequest('Пользователь не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении пользователя'));
        }
    },

    getUsersByEmail: async (req, res, next) => {
        try {
            const email = req.params.email;
            const user = await User.getUsersByEmail(email);
            if (user) {
                res.json(user);
            } else {
                next(ApiError.badRequest('Пользователь не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении пользователя'));
        }
    },

    create: async (req, res, next) => {
        try {
            const { name, info, avatar, idAuthorized } = req.body;
            const user = await User.create(name, info, avatar, idAuthorized);
            res.json(user);
        } catch (error) {
            next(ApiError.internal('Ошибка при создании пользователя'));
        }
    },

    update: async (req, res, next) => {
        try {
            const { USER_NAME, USER_INFO } = req.body;
            const id = parseInt(req.params.id);
            const user = await User.updateUsers(id, USER_NAME, USER_INFO);
            res.json(user);
        } catch (error) {
            next(ApiError.internal('Ошибка при обновлении пользователя'));
        }
    },

    delete: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            //Удалить все значения из связанных таблиц
            //Комментарии   
            console.log(id);
            const comments = await User.deleteComments(id);
            //Закладки
            console.log('delcom');
            const bookmarks = await User.deleteBookmarks(id);
            console.log('delbook');
            const user = await User.deleteUsers(id);
            res.json(user);
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении пользователя'));
        }
    },

    changeRoleToAuthor: async (req, res, next) => {
        try {
          const { email } = req.body;
      
          // Проверяем, существует ли пользователь с таким email
          const user = await prisma.users.findUnique({
            where: { EMAIL: email },
          });
      
          if (!user) {
            return next(ApiError.badRequest('Пользователь с таким email не найден.'));
          }
      
          // Проверяем, имеет ли пользователь роль USER
          if (user.ACCESS_LEVEL !== 'USER') {
            return next(ApiError.badRequest('Пользователя нельзя назначить автором.'));
          }
      
          const authorName = user.USER_NAME || email.split('@')[0];
      
          // Используем транзакцию для изменения роли и добавления автора
          await prisma.$transaction(async (prisma) => {
            // Обновляем роль пользователя на AUTHOR
            await prisma.users.update({
              where: { ID: user.ID },
              data: { ACCESS_LEVEL: 'AUTHOR' },
            });
      
            // Добавляем запись в таблицу authors, если ее еще нет
            const existingAuthor = await prisma.authors.findFirst({
              where: { ID_USER: user.ID },
            });
      
            if (!existingAuthor) {
              await prisma.authors.create({
                data: {
                  AUTHOR_NAME: authorName,
                  ID_USER: user.ID,
                },
              });
            }
          });
      
          res.json({ message: 'Пользователь успешно назначен автором.' });
        } catch (error) {
          console.error('Ошибка в changeRoleToAuthor:', error);
          next(ApiError.internal(`Ошибка при назначении пользователя автором: ${error.message}`));
        }
    }      
};

module.exports = UsersController;
