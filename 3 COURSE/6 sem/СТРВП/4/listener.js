var http = require('http')
var url = require('url')
var fs = require('fs')
var data = require('./index.js')

var db = new data.DB()


db.on('GET', (req, resp)=>{
    console.log('GET'); 
    resp.writeHead(200, {'Content-Type': 'application/json; charset = utf-8', "Access-Control-Allow-Origin": "*" });
    resp.end(JSON.stringify(db.select()))
})

db.on('POST',  (req, resp)=>{
    console.log('POST'); 
    req.on('data', data => {
        let row = JSON.parse(data);
        row.id = db.getIndex();
        db.insert(row);
        resp.end(JSON.stringify(row));
        console.log(row);
    });
})

db.on('PUT', (req, resp)=>{
    console.log('PUT')
    req.on('data', data => {
        let row = JSON.parse(data);
        db.update(row);
        resp.writeHead(200, {'Content-Type': 'application/json; charset = utf-8', "Access-Control-Allow-Origin": "*" });
        resp.end(JSON.stringify(row));
    });
})

db.on('DELETE', (req, resp)=>{
    console.log('DELETE')
    if (url.parse(req.url, true).query.id !== null)
    {
        let index = url.parse(req.url, true).query.id
        let row = db.delete(index);
        resp.end(JSON.stringify(row));   
    }
})

http.createServer((req, resp) => {
	if(url.parse(req.url).pathname === '/api/db') {
		db.emit(req.method, req, resp);
	}
	if(url.parse(req.url).pathname === '/') {
        let page = fs.readFileSync('./index.html');
        resp.writeHead(200, {'Content-Type' : 'text/html; charset=utf-8'});
        resp.end(page);
    }
}).listen(5000);
