const client = require('@prisma/client');
const ApiError = require('../error/ApiError');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);

const prisma = new client.PrismaClient();
//Получить данные
async function getBookMarks() {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take
    });
}

async function getBookMarksById(id) {
    return await prisma.user_bookmarks.findUnique({
        where: {
            ID: id,
        },
    });
}
//TODO: Идет проверка
async function getBookMarksByUserIdAndBookId(id_user, id_book) {
    id_user = parseInt(id_user);
    return await prisma.user_bookmarks.findMany({
        where: {
            USERID: id_user,
            BOOKID: id_book,
        },
    });
}

async function getBookMarksByUserId(id, sort, page) {
    console.log(sort, id, page);
    count = await prisma.user_bookmarks.count({
        where: {
            USERID: id,
            STATUS_READING: sort,
        },
    });
    marks = await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id,
            STATUS_READING: sort,
        },
    });
    let Nmarks = [];
    for (let i = 0; i < marks.length; i++) {
        book = await prisma.books.findUnique({
            where: {
                ID: marks[i].BOOKID,
            },
        });
        Nmarks[i] = {
            book: book,
            data: marks[i].DATA_ADD,
            data_read: marks[i].DATA_READING,
        }
    }
    console.log(Nmarks);
    return {
        marks: Nmarks,
        totalPages: Math.ceil(count / take),
    }
}

async function getBookMarksByBookId(id, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            BOOKID: id,
        },
    });
}
//Сортировки
async function getBookMarksByDate(page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        orderBy: {
            DATE: 'desc',
        },
    });
}

async function getBookMarksByDateAndRating(page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        orderBy: {
            DATE: 'desc',
            RATING: 'desc',
        },
    });
}
//Сортировки конретного пользователя
async function getBookMarksByDateAndRatingbyUser(id_user, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
        },
        orderBy: {
            DATE: 'desc',
            RATING: 'desc',
        },
    });
}
async function getBookMarksByDatebyUser(id_user, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
        },
        orderBy: {
            DATE: 'desc',
        },
    });
}

async function getBookMarksByRatingbyUser(id_user, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
        },
        orderBy: {
            RATING: 'desc',
        },
    });
}

async function getBookMarksByUserandStatusReading(id_user, status_reading, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
            STATUS_READING: status_reading,
        },
    });
}

async function getBookMarksByUserandStatusReadingandDate(id_user, status_reading, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
            STATUS_READING: status_reading,
        },
        orderBy: {
            DATE: 'desc',
        },
    });
}
async function getBookMarksByUserandStatusReadingandRating(id_user, status_reading, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
            STATUS_READING: status_reading,
        },
        orderBy: {
            RATING: 'desc',
        },
    });
}

async function getBookMarksByUserandPresence(id_user, Presence, page) {
    return await prisma.user_bookmarks.findMany({
        skip: skip(page),
        take: take,
        where: {
            USERID: id_user,
            PRESENCE: Presence,
        },
    });
}
//Добавить данные
async function addBookMarks(user, book, read, page) {
    mark = await prisma.user_bookmarks.findMany({
        where: {
            USERID: parseInt(user),
            BOOKID: parseInt(book),
        },
    });
    console.log(user);
    if (mark.length > 0) {
        return await prisma.user_bookmarks.update({
            where: {
                ID: mark[0].ID,
            },
            data: {
                USERID: parseInt(user),
                BOOKID: parseInt(book),
                STATUS_READING: read,
                DATA_READING: new Date(),
                MARKS: page,
            },
        });
    }
    return await prisma.user_bookmarks.create({
        data: {
            USERID: parseInt(user),
            BOOKID: parseInt(book),
            DATA_ADD: new Date(),
            DATA_READING: new Date(),
            STATUS_READING: read,
            MARKS: page,
        },
    });
}

//Изменить данные
async function updateBookMarks(id, Marks, DATE, RATING, PRESENCE) {
    return await prisma.user_bookmarks.update({
        where: {
            ID: id,
        },
        data: {
            MARKS: Marks,
            DATE: DATE,
            RATING: RATING,
            PRESENCE: PRESENCE,
        },
    });
}

async function addMarks(id, Marks, DATE) {
    return await prisma.user_bookmarks.update({
        where: {
            id: id,
        },
        data: {
            MARKS: Marks,
            DATE: DATE,
        },
    });
}
async function addPresence(id, Presence) {
    return await prisma.user_bookmarks.update({
        where: {
            id: id,
        },
        data: {
            PRESENCE: Presence,
        },
    });
}
async function updateStatusReading(id_user, id_book, reading) {
    id = await prisma.user_bookmarks.findMany({
        where: {
            USERID: id_user,
            BOOKID: id_book,
        },
    });
    if (id.length == 0) {
        return await prisma.user_bookmarks.create({

            data: {
                USERID: id_user,
                BOOKID: id_book,
                STATUS_READING: "История",
                MARKS: reading,
                DATA_READING: new Date(),
                DATA_ADD: new Date(),
            },
        });
    }
    return await prisma.user_bookmarks.update({
        where: {
            ID: id[0].ID,
        },
        data: {
            MARKS: reading,
            DATA_READING: new Date(),
        },
    });
}

//Удалить данные
async function deleteBookMarks(id) {
    return await prisma.user_bookmarks.delete({
        where: {
            id: id,
        },
    });
}

module.exports = { getBookMarks, getBookMarksById, getBookMarksByUserId, getBookMarksByBookId, getBookMarksByDate, getBookMarksByDateAndRating, getBookMarksByDateAndRatingbyUser, getBookMarksByDatebyUser, getBookMarksByRatingbyUser, getBookMarksByUserandStatusReading, getBookMarksByUserandStatusReadingandDate, getBookMarksByUserandStatusReadingandRating, getBookMarksByUserandPresence, getBookMarksByUserIdAndBookId, addBookMarks, updateBookMarks, addMarks, addPresence, updateStatusReading, deleteBookMarks };
