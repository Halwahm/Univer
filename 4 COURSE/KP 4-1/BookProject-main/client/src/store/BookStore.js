import {makeAutoObservable} from "mobx";

export default class BookStore {
    constructor() {
        this._ganres = [];
        this._author = [];
        this._tags = [];
        this._books = []
        this._selectedGanre = {};
        this._selectedAuthor = {};
        this._selectedTags = [];
        makeAutoObservable(this);
    }

    setGanre(ganres) {
        this._ganres = ganres;
    }
    setAuthor(author) {
        this._author = author;
    }
    setTags(tags) {
        this._tags = tags;
    }
    setBooks(books) {
        this._books = books;
    }

    setSelectedGanre(ganre){
        console.log(ganre)
        this._selectedGanre = ganre;
    }
    setSelectedAuthor(author){
        this._selectedAuthor = author;
    }
    setSelectedTags(tags){
        this._selectedTags = tags;
    }

    get ganres() {
        return this._ganres;
    }
    get author() {
        return this._author;
    }
    get tags() {
        return this._tags;
    }
    get selectedGanre() {
        return this._selectedGanre;
    }
    get selectedAuthor() {
        return this._selectedAuthor;
    }
    get selectedTags() {
        return this._selectedTags;
    }
    get books() {
        return this._books;
    }
}