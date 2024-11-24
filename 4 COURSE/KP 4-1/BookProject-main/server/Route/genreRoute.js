const Route = require('express').Router();
const genreController = require('../Controller/genreController');
const checkRole = require('../middleware/checkRoleMiddleware');


Route.post('/', checkRole('ADMIN'),  genreController.createGenre);
Route.delete('/:id', checkRole('ADMIN'), genreController.deleteGenreById);

Route.get('/:page', genreController.getGenres);
Route.get('/book/:id', genreController.getBookGenres);
Route.delete('/book/:id/:genre', checkRole('ADMIN'), genreController.deleteGenre);
Route.post('/book/:id', checkRole('ADMIN'), genreController.addGenre);

module.exports = Route;