/* eslint-disable no-dupe-class-members */
import {getBookId} from '../http/bookAPI.js';
export default class Book {
    constructor() {
        this._id = null;
        this._name = '';
        this._status = false;
        this._series = '';
        this._author = '';
        this._chapters = null;
        this._genre = [];
        this._year = '';
        this._description = '';
        this._rating = 0;
        this._bookmarks = 0;
        this._tags = [];
    }

    setBook(book) {
        this._id = book.ID;
        this._name = book.BOOK_NAME;
        this._status = book.BOOK_STATUS;
        this._series = book.BOOK_SERIES;
        this._year = book.DATA_RELEASE;
        this._description = book.BOOK_DESCRIPTION;
        this._chapters = book.CHAPTERS;
        //Делайем запрос к серверу и получаем автора
        // this._author = getBookauthor(book.id);
        // this._rating = getBookAvarageRaiting(book.id);
        // this._bookmarks = getBookReadCount(book.id);
        // this._tags = getBookTags(book.id);
        // this._genre = getBookGenre(book.genre);
    }

    get name() {
        return this._name;
    }

    get status() {
        return this._status;
    }

    get series() {
        return this._series;
    }
    get author() {
        return this._author;
    }
    get genre() {
        return this._genre;
    }
    get year() {
        return this._year;
    }
    get description() {
        return this._description;
    }
    get rating() {
        return this._rating;
    }
    get comments() {
        return this._comments;
    }
    get bookmarks() {
        return this._bookmarks;
    }
    get tags() {
        return this._tags;
    }
    get genre() {
        return this._genre;
    }
    get id() {
        return this._id;
    }
    get chapters() {
        return this._chapters;
    }

    setid(id) {
        this._id = id;
    }

    setname(name) {
        this._name = name;
    }

    setBookmark(bookmarks) {
        this._marks = bookmarks;
    }   


}