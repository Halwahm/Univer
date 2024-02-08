const http = require('http');
const query = require('querystring');
const url = require('url');

http.createServer(function(request, response) {
    let parsedQ;
    let data = '';
    request.on('data', chunk => {
        data += chunk.toString();
    })
    request.on('end', () => {
    //let parsedQ = url.parse(request.url, true).query;
    parsedQ = JSON.parse(data);
    response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
    response.end(`<h1>x = ${parsedQ.x}; y = ${parsedQ.y}; s = ${parsedQ.s}</h1>`);
    });
}).listen(5000);

//let parameters = query.stringify({x: 2, y: 8, s: 'aaa'});
//console.log(`params: ${parameters}`);
let path = `/`;

let options = {
    host: 'localhost',
    path: path,
    port: 5000,
    method: 'POST',
    headers: {
        'content-type' : 'appliation/json', 
        'accept' : 'application/json'
    }
};

let request = http.request(options, (res) => {
    console.log(`Response status: ${res.statusCode}`);

    let data= '';
    res.on('data', (chunk) => {
        console.log(`body: ${data += chunk.toString('utf8')}`);
    });


});

request.end(JSON.stringify({x: 2, y: 8, s: 'aaa'}));
