const Route = require('express').Router();
const UserRoute = require('./usersRoute');
const BookRoute = require('./booksRoute');
const FeedbackRoute = require('./feedbackRoute');
const BookmarkRoute = require('./bookmarksRoute');
const fileRoute = require('./filesRoute');
const tagRoute = require('./tagRoute');
const genreRoute = require('./genreRoute');
const authorRoute = require('./authorRoute');
const path = require('path');


Route.use('/users', UserRoute);
Route.use('/books', BookRoute);
Route.use('/feedback', FeedbackRoute);
Route.use('/bookmark', BookmarkRoute);
Route.use('/files', fileRoute);
Route.use('/tag', tagRoute);
Route.use('/genre', genreRoute);
Route.use('/author', authorRoute);

module.exports = Route;