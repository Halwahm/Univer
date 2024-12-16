const Route = require('express').Router();
const bookController = require('../Controller/booksController');
const checkRole = require('../middleware/checkRoleMiddleware');

Route.get('/:page', bookController.getBooks);
Route.post('/filter/:page', bookController.getBooksFilter);
Route.post('/search/:page', bookController.getBookSearch);
Route.get('/id/:id', bookController.getBookById);
Route.get('/raiting/:id', bookController.getBookAvarageRaiting);

// Route.get('/name/:name', bookController.getBooksByName);
// Route.get('/series/:series/:page', bookController.getBooksBySeries);
// Route.get('/author/:author/:page', bookController.getBooksByAuthor);
// Route.get('/genre/:genre/:page', bookController.getBooksByGenre);
// Route.get('/status/:status/:page', bookController.getBooksByStatus);

//Удаление, добавление, изменение данных
Route.post('/', checkRole(['AUTHOR', 'ADMIN']), bookController.create);
Route.put('/:id', checkRole(['AUTHOR', 'ADMIN']), bookController.update);
Route.delete('/:id', checkRole(['AUTHOR', 'ADMIN']), bookController.delete);

Route.get('/author/:userId/:page', checkRole(['AUTHOR', 'ADMIN']), bookController.getBooksByAuthor);

module.exports = Route;
