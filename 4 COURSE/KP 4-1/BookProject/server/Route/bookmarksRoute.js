const Route = require('express').Router();
const bookmarkController = require('../Controller/user_bookmarksController');
const authMiddleware = require('../middleware/authMiddleware');
const checkRole = require('../middleware/checkRoleMiddleware');

Route.get('/:page', authMiddleware, bookmarkController.getBookMarks);
Route.get('/:id', authMiddleware, bookmarkController.getBookMarksById);
Route.get('/user/:id', authMiddleware, bookmarkController.getBookMarksByUserId);


//Добавить закладку
Route.post('/', authMiddleware, bookmarkController.createBookMark);
//Получить закладку по id пользователя и id книги
Route.get('/user/:id_user/:id_book', authMiddleware, bookmarkController.getBookMarksByUserIdAndBookId);


//getStatusReading
Route.get('/status/:id/:reading', authMiddleware, bookmarkController.statusReading);
//updateStatusReading
Route.put('/status/', authMiddleware, bookmarkController.updateStatusReading);
//getBookMarksUser
Route.get('/user/:id/:sort/:page', authMiddleware, bookmarkController.getBookMarksByUserId);





module.exports = Route;