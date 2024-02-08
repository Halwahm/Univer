var http = require('http');

http.createServer(function(request, response) {
    if(request.method === 'GET') {
        response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
        response.end('<h1>Hi</h1>');
    }
}).listen(5000);

let options = {
    host: 'localhost',
    path: '/',
    port: 5000,
    method: 'GET'
}

const req = http.request( options, (res) =>{
    console.log(`Response status: ${res.statusCode}\nStatus message: ${res.statusMessage}`);
    console.log(`Server IP: ${res.socket.remoteAddress}\nServer port: ${res.socket.remotePort}`);
    console.log(`Response headers: ${res.headers}`);

    let data = '';
    res.on('data', (chunk) => {
        console.log(`body: ${data += chunk.toString('utf8')}`);
    });
    res.on('end', () => {console.log(`end: ${data}`)})
});

req.on('error', (e) => {
    console.log('Error', e.message);
});
req.end();