const BookMark = require('../Model/user_bookmarks');
const ApiError = require('../error/ApiError');

const BookMarkController = {
    getBookMarks: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            const bookmarks = await BookMark.getBookMarks(page);
            res.json(bookmarks);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладок'));
        }
    },

    getBookMarksById: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const bookmark = await BookMark.getBookMarksById(id);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Закладка не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладки'));
        }
    },

    getBookMarksByUserIdAndBookId: async (req, res, next) => {
        try {
            const id_user = parseInt(req.params.id_user);
            const id_book = parseInt(req.params.id_book);
            const bookmark = await BookMark.getBookMarksByUserIdAndBookId(id_user, id_book);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Закладка не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладки'));
        }
    },

    getBookMarksByUserId: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const sort = req.params.sort;
            const page = parseInt(req.params.page);
            const bookmark = await BookMark.getBookMarksByUserId(id, sort, page);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Закладки не найдены'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладок'));
        }
    },

    getBookMarksByBookId: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const bookmark = await BookMark.getBookMarksByBookId(id);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Закладки не найдены'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладок'));
        }
    },

    statusReading: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const reading = req.params.reading;
            const bookmark = await BookMark.getBookMarksByUserandStatusReading(id, reading);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Закладок не найдено'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении закладок'));
        }
    },

    createBookMark: async (req, res, next) => {
        try {
            const { id_user, id_book, page, marks } = req.body;
            console.log(id_user, id_book, page, marks);
            const bookmark = await BookMark.addBookMarks(id_user, id_book, marks, page);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Ошибка создания закладки'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при создании закладки'));
        }
    },

    addMark: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const bookmark = await BookMark.addMark(id);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Ошибка добавления закладки'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при добавлении закладки'));
        }
    },

    addPresence: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const bookmark = await BookMark.addPresence(id);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Ошибка изменения статуса закладки'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при изменении статуса закладки'));
        }
    },

    updateStatusReading: async (req, res, next) => {
        try {
            const id = parseInt(req.body.id_user);
            const id_book = parseInt(req.body.id_book);
            const reading = req.body.marks;
            const bookmark = await BookMark.updateStatusReading(id, id_book, reading);
            if (bookmark) {
                res.json(bookmark);
            } else {
                next(ApiError.badRequest('Ошибка изменения статуса закладки'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при изменении статуса закладки'));
        }
    }
};

module.exports = BookMarkController;
