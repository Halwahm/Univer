const http = require('http');
const fs = require('fs');

http.createServer(function(request, response) {
    response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
    let readableStream = fs.createReadStream('MyPic.png');
    readableStream.on('end', () => {
        response.end();
    });

    readableStream.pipe(response);
}).listen(5000);

let writeableStream = fs.createWriteStream('MyPic2.png');

let options = {
    host: 'localhost',
    path: '/',
    port: 5000,
    method: 'GET'
};

let req = http.request(options, (res) => {
    res.pipe(writeableStream);
});
req.end();
