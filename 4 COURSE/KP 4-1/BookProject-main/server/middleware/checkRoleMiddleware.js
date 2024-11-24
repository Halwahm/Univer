const jwt = require('jsonwebtoken');
const ApiError = require('../error/ApiError');
const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

module.exports = function (roles) {
    return async function (req, res, next) {
        if (req.method === 'OPTIONS') {
            return next();
        }

        try {
            const token = req.headers.authorization.split(' ')[1];
            if (!token) {
                return next(ApiError.unauthorized('Не авторизован (токен не найден)'));
            }

            const decoded = jwt.verify(token, process.env.SECRET_KEY);
            req.user = decoded;

            // Если роль пользователя соответствует допустимым ролям, пропускаем
            if (roles.includes(decoded.role)) {
                // Если администратор, ему доступ ко всему
                if (decoded.role === 'ADMIN') {
                    return next();
                }

                // Если это автор, дополнительно проверяем связь с книгой (для PUT/DELETE)
                if (decoded.role === 'AUTHOR' && ['PUT', 'DELETE'].includes(req.method)) {
                    const bookId = parseInt(req.params.id);
                
                    if (isNaN(bookId)) {
                        return next(ApiError.badRequest('Некорректный ID книги'));
                    }
                
                    // Находим автора, связанного с текущим пользователем
                    const author = await prisma.authors.findFirst({
                        where: {
                            ID_USER: decoded.id, // decoded.id из JWT — это ID пользователя
                        },
                    });
                
                    if (!author) {
                        return next(ApiError.forbidden('Вы не являетесь автором'));
                    }
                
                    // Проверяем связь автора с книгой
                    const bookAuthor = await prisma.book_author.findFirst({
                        where: {
                            AUTHORID: author.ID, // Используем ID автора
                            BOOKID: bookId,
                        },
                    });
                
                    if (!bookAuthor) {
                        return next(ApiError.forbidden('Вы не можете редактировать или удалять эту книгу'));
                    }
                }
                
                return next();
            }

            return next(ApiError.forbidden('У вас нет прав для выполнения этого действия'));
        } catch (e) {
            console.error('Ошибка авторизации:', e.message);
            return next(ApiError.unauthorized('Ошибка авторизации: ' + e.message));
        }
    };
};
