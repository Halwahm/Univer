var http = require('http');
var fs = require('fs');

http.createServer(function (request, response) {
    let html = fs.readFileSync('./index.html')
    response.writeHead(200, {'Content-Type': 'text/html'});
    response.end(html);
}).listen(5000);

console.log('Server running at http://localhost:5000/');