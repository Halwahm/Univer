const Route = require('express').Router();
const userController = require('../Controller/usersController');
const authMiddleware = require('../middleware/authMiddleware');

Route.post('/registration', userController.registration);
Route.post('/login', userController.login);
Route.get('/auth', authMiddleware, userController.check);

Route.get('/:page', userController.getUsers);
Route.get('/id/:id', userController.getUsersById);
Route.get('/authorized/:id', userController.getUserAuthorized);
Route.get('/email/:email', userController.getUsersByEmail);

//Изменение данных пользователя
Route.put('/change/:id', authMiddleware, userController.update);
//Удаление пользователя
Route.delete('/:id', authMiddleware,  userController.delete);

Route.put('/change-role', authMiddleware, userController.changeRoleToAuthor);

module.exports = Route;
