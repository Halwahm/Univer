const ApiError = require('../error/ApiError');
const Author = require('../Model/author');

const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

const AuthorController = {
    addAuthor: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const author = req.body;
            const result = await Author.addAuthorforBook(id, author);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при добавлении автора для книги'));
        }
    },

    deleteAuthor: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const author = parseInt(req.params.author);
            const result = await Author.deleteAuthorforBook(id, author);
            if (result) {
                res.json(result);
            } else {
                next(ApiError.badRequest('Автор не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении автора для книги'));
        }
    },

    createAuthor: async (req, res, next) => {
        try {
            const author = req.body;
            const result = await Author.addAuthor(author);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при создании автора'));
        }
    },

    getAuthors: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            const authors = await Author.getAuthors(page);
            res.json(authors);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении авторов'));
        }
    },

    getBookAuthors: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const authors = await Author.getBookAuthors(id);
            res.json(authors);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении авторов книги'));
        }
    },
    updateAuthor: async (req, res, next) => {
        try {
            const author = req.body;
            const id = parseInt(req.params.id);
            const result = await Author.updateAuthor(id, author);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при обновлении автора'));
        }
    },
    delete: async (req, res, next) => {
        try {
            const { id } = req.params;

            // Проверяем, существует ли автор с таким ID
            const author = await prisma.authors.findUnique({
                where: { ID: parseInt(id) },
            });

            if (!author) {
                return next(ApiError.badRequest('Автор с таким ID не найден.'));
            }

            // Используем транзакцию для удаления автора и изменения роли пользователя
            await prisma.$transaction(async (prisma) => {
                // Удаляем запись из таблицы authors
                await prisma.authors.delete({
                    where: { ID: parseInt(id) },
                });

                // Обновляем роль пользователя обратно на USER
                await prisma.users.update({
                    where: { ID: author.ID_USER },
                    data: { ACCESS_LEVEL: 'USER' },
                });
            });

            res.json({ message: 'Автор успешно удален.' });
        } catch (error) {
            console.error('Ошибка в deleteAuthor:', error);
            next(ApiError.internal(`Ошибка при удалении автора: ${error.message}`));
        }
    }

};

module.exports = AuthorController;
