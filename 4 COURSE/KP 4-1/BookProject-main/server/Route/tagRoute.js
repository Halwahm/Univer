const Route = require('express').Router();
const tagController = require('../Controller/tagController');
const checkRole = require('../middleware/checkRoleMiddleware');


Route.get('/:page', tagController.getTags)
Route.post('/book/:id', checkRole('ADMIN'), tagController.addTag);
Route.delete('/book/:id/:tag', checkRole('ADMIN'), tagController.deleteTag);
Route.get('/book/:id', tagController.getTagsByBook);
Route.post('/',checkRole('ADMIN'), tagController.create);
Route.delete('/:id', checkRole('ADMIN'), tagController.delete);

module.exports = Route;
