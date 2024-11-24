const Tag = require('../Model/tag');
const ApiError = require('../error/ApiError');

const TagController = {
    //Получить все теги по страницам
    getTags: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            const tags = await Tag.getTags(page);
            res.json(tags);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении списка тегов'));
        }
    },
    //Добавить тег для книги
    addTag: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const tag = req.body;
            console.log(tag);
            const result = await Tag.addTagforBook(id, tag);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при добавлении тега для книги'));
        }
    },
    //Удалить тег для книги
    deleteTag: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const tag = parseInt(req.params.tag);
            console.log(tag, id);
            const result = await Tag.deleteTagforBook(id, tag);
            if (result) {
                res.json(result);
            }
            else {
                next(ApiError.notFound('Тег не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении тега для книги'));
        }
    },
    getTagsByBook: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const tags = await Tag.getBookTags(id);
            res.json(tags);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении тегов для книги'));
        }
    },
    //Удалить тег
    delete: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const result = await Tag.deleteTag(id);
            if (result) {
                res.json(result);
            }
            else {
                next(ApiError.notFound('Тег не найден'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при удалении тега'));
        }
    },
    //Добавить тег
    create: async (req, res, next) => {
        try {
            const tag = req.body;
            const result = await Tag.createTag(tag);
            res.json(result);
        } catch (error) {
            next(ApiError.internal('Ошибка при создании тега'));
        }
    }
};

module.exports = TagController;
