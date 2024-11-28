const client = require('@prisma/client');
const ApiError = require('../error/ApiError');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);

const prisma = new client.PrismaClient();


//Author
async function addAuthorforBook(id, author) {
   id_author = parseInt(author[0].ID);
    if (id_author == null) {
        return null;
    }
    return await prisma.book_author.create({
        data: {
            BOOKID: id,
            AUTHORID: id_author,
        },
    });
}
//+
async function deleteAuthorforBook(id, author) {
    idauthor = parseInt(author);
    id = parseInt(id);
    id_author = await prisma.authors.findUnique({
        where: {
            ID: idauthor,
        },
    });
    if (id_author == null) {
        return null;
    }
    del = await prisma.book_author.findMany({
        where: {
            BOOKID: id,
            AUTHORID: idauthor,
        },
    });

    return await prisma.book_author.delete({
        where: {
            ID: del[0].ID,
        },
    });
}

async function addAuthor(author) {
    return await prisma.authors.create({
        data: {
            AUTHOR_NAME: author.name,
            ID_USER: author.ID_USER, 
        },
    });
}


async function getAuthors(page) {
    if (page == 0) {
        return await prisma.authors.findMany();
    }
    totalPages = Math.ceil(await prisma.authors.count() / take);
    const authors = await prisma.authors.findMany({
        skip: skip(page),
        take: take,
    });
    return {
        authors: authors,
        totalPages: totalPages,
    }
}

async function deleteAuthor(id) {
    return await prisma.authors.delete({
        where: {
            ID: id,
        },
    });
}
//+
async function getBookAuthors(id) {
    ID_AUTHORS = await prisma.book_author.findMany({
        where: {
            BOOKID: id,
        },
    });
    const authors = [];
    for (let i = 0; i < ID_AUTHORS.length; i++) {
        authors[i] = await prisma.authors.findUnique({
            where: {
                ID: ID_AUTHORS[i].AUTHORID,
            },
        });
    }
    return authors;
}

async function updateAuthor(id, author) {
    return await prisma.authors.update({
        where: {
            ID: id,
        },
        data: {
            AUTHOR_NAME: author.name,
        },
    });
}

async function deleteA(id) {
    await prisma.book_author.deleteMany({
        where: {
            AUTHORID: id,
        },
    });
    return await prisma.authors.delete({
        where: {
            ID: id,
        },
    });
}

module.exports = {
    getAuthors,
    addAuthor,
    deleteAuthor,
    addAuthorforBook,
    deleteAuthorforBook,
    getBookAuthors,
    updateAuthor,
    deleteA,
};