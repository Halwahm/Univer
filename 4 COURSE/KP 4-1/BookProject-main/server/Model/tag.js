const client = require('@prisma/client');
const ApiError = require('../error/ApiError');
const skip = require('../static/Math').skip;
const take = parseInt(process.env.TAKE_ITEM);
const prisma = new client.PrismaClient();


//Tags
async function getTags(page) {
    if (page == 0) {
        return await prisma.tag.findMany();
    }
    totalPages = Math.ceil(await prisma.tag.count() / take);
   const tags = await prisma.tag.findMany({
        skip: skip(page),
        take:  take
    });
    return {
        tags: tags,
        totalPages: totalPages,
    }
}
async function getBookTags(id) {
    ID_TAGS = await prisma.book_tag.findMany({
        where: {
            BOOKID: id,
        },
    });
    const tags = [];
    for (let i = 0; i < ID_TAGS.length; i++) {
        tags[i] = await prisma.tag.findUnique({
            where: {
                ID: ID_TAGS[i].TAGID,
            },
        });
    }
    return tags;
}
async function addTagforBook(id, tag) {
    id_tag = parseInt(tag[0].ID);
    if (id_tag == null) {
        return null;
    }
    return await prisma.book_tag.create({
        data: {
            BOOKID: id,
            TAGID: id_tag,
        },
    });
}
async function deleteTagforBook(id, tag) {
    idtag = parseInt(tag);
    id = parseInt(id);
    id_tag = await prisma.tag.findUnique({
        where: {
            ID: idtag,
        },
    });
    if (id_tag == null) {
        return null;
    }
    del = await prisma.book_tag.findMany({
        where: {
            BOOKID: id,
            TAGID: idtag,
        },
    });
    console.log(del);
    return await prisma.book_tag.delete({
        where: {
            ID: del[0].ID,
        },
    });
}
async function deleteTag(id) {
    id = parseInt(id);
    await prisma.book_tag.deleteMany({
        where: {
            TAGID: id,
        },
    });
    return await prisma.tag.delete({
        where: {
            ID: id,
        },
    });
}
async function createTag(tag) {
    return await prisma.tag.create({
        data: {
            TAG_NAME: tag.name,
        },
});
}



//Экспорт
module.exports = {
    getTags,
    getBookTags,
    addTagforBook,
    deleteTagforBook,
    deleteTag,
    createTag,
}