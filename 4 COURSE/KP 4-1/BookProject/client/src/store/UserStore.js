import {makeAutoObservable} from "mobx";
import {getUserInfo, getFeedback, getBookmarks} from "../http/userAPI";




export default class UserStore {
    constructor() {
        this.id = null;
        this._isAuth = false;
        this._user = {};
        this._Name = "";
        this._info = "";
        this._DataCreate = "";
        this._comments = [];
        this._marks = [];
        makeAutoObservable(this);
    }

    setIsAuth(bool) {
        this._isAuth = bool;
    }
    setUser(user) {
            this._user = user;
    }
    setComments(id) {
        this.comments = getFeedback(id);
    }

    setBookmark(bookmarks) {
        this._marks = bookmarks;
    }

    get isAuth() {
        return this._isAuth;
    }
    get user() {
        return this._user;
    }

    get token() {
        return this._token;
    }

    get content() {
        return this._content;
    }
    get name() {
        return this._Name;
    }
    get Info() {
        return this._info;
    }
    get dataCreate() {
        return this._DataCreate;
    }
    get marks() {
        return this._marks;
    }
    get comments() {
        return this._comments;
    }

    checkAdmin() {
        const token = localStorage.getItem('token');
        if (token === null) {
            return false;
        }
        const role = localStorage.getItem('role');
        if (role === "ADMIN") {
            return true;
        }
        return false;
    }
    
    checkAuthor() {
        // const token = localStorage.getItem('token');
        // if (token === null) {
        //     return false;
        // }
        const role = localStorage.getItem('role');
        if (role === "AUTHOR") {
            return true;
        }
        return false;
    }
}