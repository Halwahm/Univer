const {verify}= require('jsonwebtoken');
const ApiError = require('../error/ApiError.js');

module.exports = function (req, res, next) {
    if (req.method === 'OPTIONS') {
       return next();
    }
    try {
        console.log("req.headers.authorization: ", req.headers.authorization);
        const token = req.headers.authorization.split(' ')[1];
        if (!token) {
            return next(ApiError.unauthorized('Нe авторизован(Не передан токен)'));
        }
        console.log(token);
        
        const decoded = verify(token, process.env.SECRET_KEY);
        req.user = decoded;
        console.log("decoded: ", decoded);
        return next();
    }
    catch (e) {
        return next(ApiError.unauthorized('Не авторизован(Непредвиденная ошибка)'+e.message));
    }
}