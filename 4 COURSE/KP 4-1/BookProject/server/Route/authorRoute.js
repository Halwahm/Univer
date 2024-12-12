const Route = require('express').Router();
const authorController = require('../Controller/authorController');
const checkRole = require('../middleware/checkRoleMiddleware');


Route.get('/:page', authorController.getAuthors);
Route.post('/book/:id', checkRole('ADMIN'), authorController.addAuthor);
Route.delete('/book/:id/:author', checkRole('ADMIN'), authorController.deleteAuthor);
Route.get('/book/:id', authorController.getBookAuthors);
Route.get('/book/:id/:book', authorController.getBookAuthors);
Route.post('/',  checkRole('ADMIN'),authorController.createAuthor);
Route.put('/:id', checkRole('ADMIN'), authorController.updateAuthor);
Route.delete('/:id', checkRole('ADMIN'), authorController.delete);

module.exports = Route;