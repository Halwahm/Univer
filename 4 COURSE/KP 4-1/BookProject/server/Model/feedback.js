const client = require('@prisma/client');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);


const prisma = new client.PrismaClient();
//Получить данные
async function getFeedback(page) {
    page = parseInt(page);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take
    });
}

async function getFeedbackById(id) {
    id = parseInt(id);
    return await prisma.feedback.findUnique({
        where: {
            id: id,
        },
    });
}

async function getFeedbackByUserId(id, page) {
    page = parseInt(page);
    id = parseInt(id);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        where: {
            ID_USER: id,
        },
    });
}

async function getFeedbackByBookId(id, page) {
    page = parseInt(page);
    id = parseInt(id);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        where: {
            ID_BOOK: id,
        },
    });
}

async function getFeedbackByRating(page) {
    page = parseInt(page);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        orderBy: {
            RATING: 'desc',
        },
    });
}

async function getFeedbackByDate(page) {
    page = parseInt(page);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        orderBy: {
            DATE: 'desc',
        },
    });
}

async function getFeedbackByDateAndRating(page) {
    page = parseInt(page);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        orderBy: {
            DATE: 'desc',
            RATING: 'desc',
        },
    });
}

async function getFeedbackByDateAndRatingbyBook(id_book, page) {
    page = parseInt(page);
    id_book = parseInt(id_book);
    return await prisma.feedback.findMany({
        skip: skip(page),
        take: take,
        where: {
            ID_BOOK: id_book,
        },
        orderBy: {
            DATE: 'desc',
            RATING: 'desc',
        },
    });
}

//Добавить данные
async function addFeedback(id_user, id_book, rating, text) {
    id_user = parseInt(id_user);
    id_book = parseInt(id_book);
    rating = parseFloat(rating);
    return await prisma.feedback.create({
        data: {
            ID_USER: id_user,
            ID_BOOK: id_book,
            RATING: rating,
            FEEDBACK: text,
        },
    });
}

//Изменить данные
async function updateFeedback(id, id_user, id_book, rating, text) {
    id = parseInt(id);
    id_user = parseInt(id_user);
    id_book = parseInt(id_book);
    rating = parseFloat(rating);
    return await prisma.feedback.update({
        where: {
            id: id,
        },
        data: {
            ID_USER: id_user,
            ID_BOOK: id_book,
            RATING: rating,
            FEEDBACK: text,
        },
    });
}

//Удалить данные
async function deleteFeedback(id) {
    id = parseInt(id);
    return await prisma.feedback.delete({
        where: {
            ID: id,
        },
    });
}

module.exports = { getFeedback, getFeedbackById, getFeedbackByUserId, getFeedbackByBookId, getFeedbackByRating, getFeedbackByDate, getFeedbackByDateAndRating, getFeedbackByDateAndRatingbyBook, addFeedback, updateFeedback, deleteFeedback };