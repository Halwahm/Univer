const ApiError = require('../error/ApiError');
const Genre = require('../Model/genre');

const GenreController = {
    getGenres: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            console.log(page);
            const genres = await Genre.getGenres(page);
            res.json(genres);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении жанров'));
        }
    },

    getBookGenres: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const genres = await Genre.getBookGenres(id);
            res.json(genres);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении жанров книги'));
        }
    },

    addGenre: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const genre = req.body;
            const result = await Genre.addGenreforBook(id, genre);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при добавлении жанра для книги'));
        }
    },

    deleteGenre: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const genre = parseInt(req.params.genre);
            console.log(genre);
            const result = await Genre.deleteGenreforBook(id, genre);
            if (result) {
                res.json(result);
            } else {
                next(ApiError.badRequest('Жанр не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении жанра для книги'));
        }
    },

    createGenre: async (req, res, next) => {
        try {
            const genre = req.body;
            const result = await Genre.addGenre(genre);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при создании жанра'));
        }
    },
    deleteGenreById: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const result = await Genre.deleteGenre(id);
            if (result) {
                res.json(result);
            } else {
                next(ApiError.badRequest('Жанр не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении жанра'));
        }
    }
};

module.exports = GenreController;
