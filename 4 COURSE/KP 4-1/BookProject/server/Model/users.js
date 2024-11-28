const client = require('@prisma/client');
const { skip} = require('../static/Math');
const ApiError = require('../error/ApiError');
const prisma = new client.PrismaClient();
const take = parseInt(process.env.TAKE_ITEM);

async function getUsers(page) {
  const totalCount = await prisma.users.count(); // получаем общее количество пользователей
  const totalPages = Math.ceil(totalCount / take); // вычисляем общее количество страниц

  const users = await prisma.users.findMany({
    skip: skip(page),
    take: take,
  });

  return {
    users: users,
    totalPages: totalPages,
  };
}

async function getUsersById(id) {
  return await prisma.users.findUnique({
    where: {
      ID: id,
    },
  });
}

async function getUsersByEmail(email) {
  return await prisma.users.findUnique({
    where: {
      EMAIL: email,
    },
  });
}

async function create(email, password, role) {
  const name = email.split('@')[0];
  return await prisma.users.create({
    data: {
      USER_NAME: name,
      USER_INFO: '',
      ACCESS_LEVEL: role,
      EMAIL: email,
      pass: password,
    },
  });
}

async function updateUsers(id, USER_NAME, USER_INFO) {
  email = await prisma.users.findMany({
    where: {
      ID: id,
    },
  });
  return await prisma.users.update({
    where: {
      EMAIL: email[0].EMAIL,
    },
    data: {
      USER_NAME: USER_NAME,
      USER_INFO: USER_INFO,
    },
  });
}

async function updateUsersAccessLevel(id, ACCESS_LEVEL) {
  return await prisma.users.update({
    where: {
      ID: id,
    },
    data: {
      ACCESS_LEVEL: ACCESS_LEVEL,
    },
  });
}

async function deleteUsers(id) {
  id = parseInt(id);
  return await prisma.users.delete({
    where: {
      ID: id,
    },
  });
}

async function deleteComments(id) {
  id = parseInt(id);
  return await prisma.feedback.deleteMany({
    where: {
      ID_USER: id,
    },
  });

}

async function deleteBookmarks(id) {
  id = parseInt(id);
  //TODO: Удаление закладок
  //Массив закладок
  return  await prisma.user_bookmarks.deleteMany({
    where: {
      USERID: id,
    },
  });

}



module.exports = {
  getUsers,
  getUsersById,
  updateUsersAccessLevel,
  deleteUsers,
  getUsersByEmail,
  updateUsers,
  create,
  deleteComments,
  deleteBookmarks,
};
