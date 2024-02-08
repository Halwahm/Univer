const http = require('http');
const query = require('querystring');
const url = require('url');

http.createServer(function(request, response) {
    let parsedQ = url.parse(request.url, true).query;
    response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
    response.end(`<h1>x = ${+parsedQ.x}; y = ${parsedQ.y}</h1>`);
}).listen(5000);

let parameters = query.stringify({x: 2, y: 8});
console.log(`params: ${parameters}`);
let path = `/?${parameters}`;

let options = {
    host: 'localhost',
    path: path,
    port: 5000,
    method: 'GET'
};

let request = http.request(options, (res) => {
    console.log(`Response status: ${res.statusCode}`);

    let data= '';
    res.on('data', (chunk) => {
        console.log(`body: ${data += chunk.toString('utf8')}`);
    });
});

request.end();
