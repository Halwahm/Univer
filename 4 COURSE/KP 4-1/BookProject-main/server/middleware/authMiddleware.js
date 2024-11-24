const {verify}= require('jsonwebtoken');
const ApiError = require('../error/ApiError.js');

module.exports = function (req, res, next) {
    if (req.method === 'OPTIONS') {
       return next();
    }
    try {
        const token = req.headers.authorization.split(' ')[1];
        if (!token) {
            return next(ApiError.unauthorized('Нe авторизован(Не передан токен)'));
        }
        const decoded = verify(token, process.env.SECRET_KEY);
        req.user = decoded;
        return next();
    }
    catch (e) {
        return next(ApiError.unauthorized('Не авторизован(Непредвиденная ошибка)'+e.message));
    }
}