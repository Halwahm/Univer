const Feedback = require('../Model/feedback');
const ApiError = require('../error/ApiError');

const FeedbackController = {
  getFeedback: async (req, res, next) => {
    try {
      const page = parseInt(req.params.page);
      const feedback = await Feedback.getFeedback(page);
      res.json(feedback);
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов'));
    }
  },

  getFeedbackById: async (req, res, next) => {
    try {
      const id = parseInt(req.params.id);
      const feedback = await Feedback.getFeedbackById(id);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзыв не найден'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзыва по ID'));
    }
  },

  getFeedbackByBookId: async (req, res, next) => {
    try {
      const id = parseInt(req.params.id);
      const page = parseInt(req.params.page);
      const feedback = await Feedback.getFeedbackByBookId(id, page);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по ID книги'));
    }
  },

  getFeedbackByUserId: async (req, res, next) => {
    try {
      const id = parseInt(req.params.id);
      const feedback = await Feedback.getFeedbackByUserId(id);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по ID пользователя'));
    }
  },

  getFeedbackByRating: async (req, res, next) => {
    try {
      const page = parseInt(req.params.page);
      const feedback = await Feedback.getFeedbackByRating(page);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по рейтингу'));
    }
  },

  getFeedbackByDate: async (req, res, next) => {
    try {
      const page = parseInt(req.params.page);
      const feedback = await Feedback.getFeedbackByDate(page);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по дате'));
    }
  },

  getFeedbackByDateAndRaiting: async (req, res, next) => {
    try {
      const page = parseInt(req.params.page);
      const feedback = await Feedback.getFeedbackByDateAndRating(page);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по дате и рейтингу'));
    }
  },

  getFeedbackByDateAndRaitingbyBook: async (req, res, next) => {
    try {
      const id = parseInt(req.params.id);
      const feedback = await Feedback.getFeedbackByDateAndRatingbyBook(id, page);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзывы не найдены'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при получении отзывов по дате, рейтингу и книге'));
    }
  },

  addFeedback: async (req, res, next) => {
    try {
      const { bookId, userId, rating, text } = req.body;
      const feedback = await Feedback.addFeedback(bookId, userId, rating, text);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзыв не добавлен'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при добавлении отзыва'));
    }
  },

  updateFeedback: async (req, res, next) => {
    try {
      const { id, bookId, userId, rating, text } = req.body;
      const feedback = await Feedback.updateFeedback(id, bookId, userId, rating, text);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзыв не обновлен'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при обновлении отзыва'));
    }
  },

  deleteFeedback: async (req, res, next) => {
    try {
      const id = parseInt(req.params.id);
      const feedback = await Feedback.deleteFeedback(id);
      if (feedback) {
        res.json(feedback);
      } else {
        next(ApiError.badRequest('Отзыв не удален'));
      }
    } catch (error) {
      next(ApiError.internal('Ошибка при удалении отзыва'));
    }
  },
};

module.exports = FeedbackController;
