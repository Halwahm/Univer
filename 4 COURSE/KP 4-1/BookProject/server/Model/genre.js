const client = require('@prisma/client');
const ApiError = require('../error/ApiError');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);

const prisma = new client.PrismaClient();


//Genre
async function getGenres(page) {
    
    if (page == 0) {
        return await prisma.genre.findMany();
    }
    totalPages = Math.ceil(await prisma.genre.count() / take);
    const genres = await prisma.genre.findMany({
        skip: skip(page),
        take: take,
    });
    return {
        genres: genres,
        totalPages: totalPages,
    }
}
//Работает
async function getBookGenres(id) {
    const genreID = await prisma.book_genre.findMany({
        where: {
           BOOKID: id,
        },
    });
    const genres = [];
    for (let i = 0; i < genreID.length; i++) {
        genres[i] =
         await prisma.genre.findUnique({
            where: {
                ID: genreID[i].GENREID,
            },
        });
    }
    return genres;
}
//Работает
async function addGenreforBook(id, genre) {
    id = parseInt(id);
    idganre = parseInt(genre[0].ID);
    console.log(idganre);
    id_genre = await prisma.genre.findUnique({
        where: {
            ID: idganre,
        },
    });
    if (id_genre == null) {
        return null;
    }
    book_genre = await prisma.book_genre.findMany({
        where: {
                BOOKID: id,
                GENREID: idganre,
        },
    })
    if (book_genre == null ) return null;
    return await prisma.book_genre.create({
        data: {
            BOOKID: id,
            GENREID: idganre,
        },
    });
}
//Работает
async function deleteGenreforBook(id, genre) {
    id = parseInt(id);
    idganre = parseInt(genre);
    id_genre = await prisma.genre.findUnique({
        where: {
            ID: idganre,
        },
    });
    if (id_genre == null) {
        return null;
    }
    del = await prisma.book_genre.findMany({
        where: {
            BOOKID: id,
            GENREID: idganre,
        }
    });
    return await prisma.book_genre.delete({
        where: {
            ID: del[0].ID,
        }
    });
}
async function addGenre(genre) {
    return await prisma.genre.create({
        data: {
            GENRE_NAME: genre.name,
        },
    });
}
async function deleteGenre(id) {
    await prisma.book_genre.deleteMany({
        where: {
            GENREID: id,
        },
    });
    return await prisma.genre.delete({
        where: {
            ID: id,
        },
    });
}

module.exports = {
    getGenres,
    getBookGenres,
    addGenreforBook,
    deleteGenreforBook,
    addGenre,
    deleteGenre,
};