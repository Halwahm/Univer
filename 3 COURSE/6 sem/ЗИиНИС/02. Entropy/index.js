const express = require("express")
const fs = require("fs").promises
const path = require("path")
const windows1251 = require("windows-1251")
const app = new express()
const open = require('open');

app.use(express.static("public"))

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "index.html"))
})

app.get("/li", async (req, res) => {
    fs.readFile("files/lith.txt").then(result => {

        result = result.toString().toUpperCase();
        res.send(result);
    });
})

app.get("/mc", async (req, res) => {
    fs.readFile("files/mac.txt").then(result => {

        result = result.toString().toUpperCase();
        //res.send(windows1251.encode(result)); 
        res.send(result);
    });
})
app.listen(3000)
open('http://localhost:3000/');