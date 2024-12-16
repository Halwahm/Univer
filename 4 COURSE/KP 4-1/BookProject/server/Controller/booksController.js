const Book = require('../Model/books');
const ApiError = require('../error/ApiError');
const client = require('@prisma/client');
const prisma = new client.PrismaClient();

const BookController = {
    getBooks: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            const books = await Book.getBooks(page, "", {});
            res.json(books);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении списка книг'));
        }
    },

    getBooksFilter: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page);
            const { searchTerm, filterParams } = req.body
            console.log('searchTerm: ', searchTerm, 'filterParams', filterParams);
            const books = await Book.getBooksFilter(page, searchTerm, filterParams);
            res.json(books);
        } catch (error) {
            next(ApiError.internal('Ошибка при получении списка книг'));
        }
    },

    getBooksByAuthor: async (req, res, next) => {
        try {
            const userId = parseInt(req.user.id);
            const page = parseInt(req.params.page) || 1;

            if (isNaN(userId) || isNaN(page)) {
                return next(ApiError.badRequest('Некорректные параметры запроса'));
            }

            const books = await Book.getBooksByAuthor(userId, page);
            if (!books || books.books.length === 0) {
                return res.json({ books: [], message: 'У вас ещё нет добавленных книг' });
            }
            
            res.json(books);
        } catch (error) {
            console.error(error);
            next(ApiError.internal('Ошибка при получении книг автора'));
        }
    },
    
    getBookSearch: async (req, res, next) => {
        try {
            const page = parseInt(req.params.page, 10) || 1;
            const search = req.body.searchTerm || '';
            const filtr = req.body.filterParams || {};
            const books = await Book.getBooks(page, search, filtr);
            res.json(books);
        } catch (error) {
            console.error("Error in getBookSearch:", error);
            next(ApiError.internal('Ошибка при поиске книги: ' + error.message));
        }
    },    

    getBookById: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const book = await Book.getBooksById(id);
            if (book) {
                res.json(book);
            } else {
                next(ApiError.badRequest('Книга не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении информации о книге'));
        }
    },

    getBookFeedbackCount: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const count = await Book.getBookFeedbackCount(id);
            if (count) {
                res.json(count);
            } else {
                next(ApiError.badRequest('Книга не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении количества отзывов о книге'));
        }
    },

    getBookReadCount: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const count = await Book.getBookReadCount(id);
            if (count) {
                res.json(count);
            } else {
                next(ApiError.badRequest('Книга не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении количества прочтений книги'));
        }
    },

    getBookAvarageRaiting: async (req, res, next) => {
        try {
            const id = parseInt(req.params.id);
            const count = await Book.getBookAverageRating(id);
            if (count) {
                res.json(count);
            } else {
                next(ApiError.badRequest('Книга не найдена'));
            }
        } catch (error) {
            next(ApiError.internal('Ошибка при получении среднего рейтинга книги'));
        }
    },

    create: async (req, res, next) => {
        try {
            const book = req.body;
            const newBook = await Book.createBook(book);
    
            if (req.user.role === 'AUTHOR') {
                await Book.linkBookToAuthor(newBook.ID, req.user.id);
            }
    
            if (book.GENRES && book.GENRES.length) {
                for (const genreId of book.GENRES) {
                    await prisma.book_genre.create({
                        data: {
                            BOOKID: newBook.ID,
                            GENREID: parseInt(genreId),
                        },
                    });
                }
            }
    
            if (book.TAGS && book.TAGS.length) {
                for (const tagId of book.TAGS) {
                    await prisma.book_tag.create({
                        data: {
                            BOOKID: newBook.ID,
                            TAGID: parseInt(tagId),
                        },
                    });
                }
            }
    
            res.json(newBook);
        } catch (e) {
            console.error('Ошибка при создании книги:', e.message);
            next(ApiError.internal('Ошибка при создании книги: ' + e.message));
        }
    },
    
    

    update: async (req, res, next) => {
        try {
            const bookId = parseInt(req.params.id);
            const { BOOK_NAME, BOOK_DESCRIPTION, BOOK_SERIES, DATA_RELEASE, CHAPTERS, GENRES, TAGS } = req.body;
    
            const existingBook = await Book.getBooksById(bookId);
            if (!existingBook) {
                return next(ApiError.badRequest("Книга не найдена"));
            }    
            const updatedBook = await Book.updateBook(bookId, {
                BOOK_NAME,
                BOOK_DESCRIPTION,
                BOOK_SERIES,
                DATA_RELEASE: parseInt(DATA_RELEASE),
                CHAPTERS: parseInt(CHAPTERS),
            });
    
            if (GENRES) {
                await Book.deleteGenresFromBook(bookId);
    
                for (const genreId of GENRES) {
                    await Book.addGenreToBook(bookId, genreId);
                }
            }
    
            if (TAGS) {
                await Book.deleteTagsFromBook(bookId);
    
                for (const tagId of TAGS) {
                    await Book.addTagToBook(bookId, tagId);
                }
            }
    
            res.json(updatedBook);
        } catch (error) {
            console.error("Ошибка при обновлении книги:", error);
            next(ApiError.internal("Ошибка при обновлении книги: " + error.message));
        }
    },
    

    delete: async (req, res, next) => {
        try {
            const bookId = parseInt(req.params.id);

            // Проверяем существование книги
            const existingBook = await Book.getBooksById(bookId);
            if (!existingBook) {
                return next(ApiError.badRequest('Книга не найдена'));
            }

            // Удаляем книгу
            const result = await Book.deleteBook(bookId);
            res.json(result);
        } catch (e) {
            next(ApiError.internal('Ошибка при удалении книги: ' + e.message));
        }
    },
};

module.exports = BookController;