const Rote = require('express').Router();
const feedbackController = require('../Controller/feedbackController');
const authMiddleware = require('../middleware/authMiddleware');

Rote.get('/:page', feedbackController.getFeedback);
Rote.get('/:id', feedbackController.getFeedbackById);
Rote.get('/user/:id/:page', feedbackController.getFeedbackByUserId);
Rote.get('/book/:id/:page', feedbackController.getFeedbackByBookId);

//Добавить отзыв
Rote.post('/', authMiddleware, feedbackController.addFeedback);
//Удалить отзыв
Rote.delete('/:id', authMiddleware, feedbackController.deleteFeedback);
//Обновить отзыв
Rote.put('/:id', authMiddleware, feedbackController.updateFeedback);

module.exports = Rote;