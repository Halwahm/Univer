const client = require('@prisma/client');
const ApiError = require('../error/ApiError');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);

const prisma = new client.PrismaClient();

async function getBooks(page, searchTerm, filterParams) {
    const where = {};

    // Поиск по названию, описанию, серии или году
    if (searchTerm) {
        const year = parseInt(searchTerm, 10);
        if (!isNaN(year)) {
            where.OR = [{ DATA_RELEASE: year }];
        } else {
            where.OR = [
                { BOOK_NAME: { contains: searchTerm } },
                { BOOK_DESCRIPTION: { contains: searchTerm } },
                { BOOK_SERIES: { contains: searchTerm } },
            ];
        }
    }

    // Фильтрация по тегам
    if (filterParams?.tags?.length) {
        where.book_tag = {
            some: {
                TAGID: {
                    in: filterParams.tags.map((item) => parseInt(item.value, 10)),
                },
            },
        };
    }

    // Фильтрация по жанрам
    if (filterParams?.genres?.length) {
        where.book_genre = {
            some: {
                GENREID: {
                    in: filterParams.genres.map((item) => parseInt(item.value, 10)),
                },
            },
        };
    }

    // Фильтрация по авторам
    if (filterParams?.authors?.length) {
        where.book_author = {
            some: {
                AUTHORID: {
                    in: filterParams.authors.map((item) => parseInt(item.value, 10)),
                },
            },
        };
    }

    console.log("Generated WHERE condition:", JSON.stringify(where, null, 2));

    try {
        // Подсчет общего количества записей
        const count = await prisma.books.count({ where });

        // Запрос книг с фильтрацией и пагинацией
        const books = await prisma.books.findMany({
            where,
            skip: skip(page),
            take: take,
            include: {
                book_tag: {
                    include: { tag: true },
                },
                book_genre: {
                    include: { genre: true },
                },
                book_author: {
                    include: { authors: true },
                },
            },
        });

        return {
            books,
            totalPages: Math.ceil(count / take),
            totalRecords: count,
        };
    } catch (error) {
        console.error("Error in getBooks:", error.message);
        throw new Error("Ошибка при выполнении запроса к базе данных");
    }
}

async function getBooksById(id) {
    return await prisma.books.findUnique({
        where: {
            ID: parseInt(id),
        },
    });
}

//Получить количество отзывов
async function getBookFeedbackCount(id) {
    return await prisma.feedback.count({
        where: {
            ID_BOOK: id,
        },
    });
}
//Получить количество прочтений
async function getBookReadCount(id) {
    return await prisma.user_bookmarks.count({
        where: {
            ID_BOOK: id,
        },
    });
}
//Получить средний рейтинг
async function getBookAverageRating(id) {
    return await prisma.feedback.aggregate({
        where: {
            ID_BOOK: id,
        },
        _avg: { RATING: true },
    });
}

async function createBook(book) {
    const chapters = parseInt(book.CHAPTERS) || null;
    const year = parseInt(book.DATA_RELEASE) || null;

    const newBook = await prisma.books.create({
        data: {
            BOOK_NAME: book.BOOK_NAME,
            BOOK_SERIES: book.BOOK_SERIES,
            DATA_RELEASE: year,
            BOOK_DESCRIPTION: book.BOOK_DESCRIPTION,
            CHAPTERS: chapters,
        },
    });
    return newBook;
}


async function updateBook(id, book) {
    console.log("book: ", book, id)
    return await prisma.books.update({
        where: { ID: id },
        data: {
            BOOK_NAME: book.BOOK_NAME,
            BOOK_SERIES: book.BOOK_SERIES,
            DATA_RELEASE: book.DATA_RELEASE,
            BOOK_DESCRIPTION: book.BOOK_DESCRIPTION,
            CHAPTERS: book.CHAPTERS,
        },
    });
}

async function linkBookToAuthor(bookId, userId) {
    // Проверяем, существует ли пользователь
    const userExists = await prisma.users.findUnique({
        where: { ID: userId },
    });

    if (!userExists) {
        throw new Error(`Пользователь с ID ${userId} не существует.`);
    }

    // Проверяем, существует ли автор с данным ID_USER в таблице AUTHORS
    let author = await prisma.authors.findFirst({
        where: { ID_USER: userId },
    });

    // Если автор не существует, создаём запись
    if (!author) {
        author = await prisma.authors.create({
            data: {
                AUTHOR_NAME: `Author_${userId}`, // Уникальное имя автора
                ID_USER: userId,                // Связываем с существующим пользователем
            },
        });
    }

    // Связываем книгу с автором
    return await prisma.book_author.create({
        data: {
            BOOKID: bookId,
            AUTHORID: author.ID, // Используем ID автора
        },
    });
}


async function deleteBook(id) {
    const bookId = parseInt(id);

    try {
        // Удаляем связи книги с авторами
        await prisma.book_author.deleteMany({
            where: {
                BOOKID: bookId,
            },
        });

        // Удаляем связи книги с жанрами
        await prisma.book_genre.deleteMany({
            where: {
                BOOKID: bookId,
            },
        });

        // Удаляем связи книги с тегами
        await prisma.book_tag.deleteMany({
            where: {
                BOOKID: bookId,
            },
        });

        // Удаляем все отзывы, связанные с книгой
        await prisma.feedback.deleteMany({
            where: {
                ID_BOOK: bookId,
            },
        });

        // Удаляем закладки, связанные с книгой
        await prisma.user_bookmarks.deleteMany({
            where: {
                BOOKID: bookId,
            },
        });

        // Удаляем саму книгу
        return await prisma.books.delete({
            where: {
                ID: bookId,
            },
        });
    } catch (error) {
        console.error("Ошибка при удалении книги:", error);
        throw new Error("Ошибка при удалении книги: " + error.message);
    }
}



async function getBooksByAuthor(userId, page) {
    const books = await prisma.books.findMany({
        where: {
            book_author: {
                some: {
                    authors: {
                        ID_USER: userId, // Проверяем, принадлежит ли книга автору
                    },
                },
            },
        },
        skip: skip(page),
        take: take,
        include: {
            book_author: {
                include: { authors: true }, // Включаем информацию об авторах
            },
        },
    });
    console.log('books: ', books);

    const count = await prisma.books.count({
        where: {
            book_author: {
                some: {
                    authors: {
                        ID_USER: userId,
                    },
                },
            },
        },
    });

    return {
        books,
        totalPages: Math.ceil(count / take),
        totalRecords: count,
    };
}

async function deleteGenresFromBook(bookId) {
    return await prisma.book_genre.deleteMany({
        where: { BOOKID: parseInt(bookId) },
    });
}

async function addGenreToBook(bookId, genreId) {
    return await prisma.book_genre.create({
        data: {
            BOOKID: parseInt(bookId),
            GENREID: parseInt(genreId),
        },
    });
}

async function deleteTagsFromBook(bookId) {
    return await prisma.book_tag.deleteMany({
        where: { BOOKID: parseInt(bookId) },
    });
}

async function addTagToBook(bookId, tagId) {
    return await prisma.book_tag.create({
        data: {
            BOOKID: parseInt(bookId),
            TAGID: parseInt(tagId),
        },
    });
}

module.exports = { getBooks, getBooksById, createBook, updateBook, 
    deleteBook, getBookFeedbackCount, getBookReadCount, getBookAverageRating, getBooksByAuthor,
    linkBookToAuthor, deleteGenresFromBook, addGenreToBook, deleteTagsFromBook, addTagToBook };
