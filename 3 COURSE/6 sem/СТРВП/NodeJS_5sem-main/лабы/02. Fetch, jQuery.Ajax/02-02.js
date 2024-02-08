var http = require('http');
var fs = require('fs');

http.createServer(function (request, response) {
    if (request.url === '/html')
    {
        let html = fs.readFileSync('./index.html')
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(html);
    }
    if(request.url === '/png')
    {
        let jpg = null; 

    fs.stat('./cat.jpg', (err, stat) => {
        if(err){
            console.log(`error: ${err}`);
        }
        else {
            jpg = fs.readFileSync('./cat.jpg');
            response.writeHead(200, {'Content-Type': 'image/jpeg', 'Content-Length': stat.size});
            response.end(jpg, 'binary');
        }
    })
    }
    if (request.url === '/api/name')
    {
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end('Merhel Caroline Andreevna');
    }
    if (request.url === '/xmlhttprequest')
    {
        let html = fs.readFileSync('./xmlhttprequest.html')
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(html);
    }
    if (request.url === '/fetch')
    {
        let html = fs.readFileSync('./fetch.html')
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(html);
    }
    if (request.url === '/jquery')
    {
        let html = fs.readFileSync('./jquery.html')
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(html);
    }
}).listen(5000);

console.log('Server running at http://localhost:5000/');