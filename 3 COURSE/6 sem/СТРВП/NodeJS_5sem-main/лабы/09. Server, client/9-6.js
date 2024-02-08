const http = require('http');
const fs = require('fs');

http.createServer(function(request, response) {
    response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
    let txt = '';
    request.on('data', (chunk) => {
        txt += chunk.toString();
        response.end(txt);
    });
}).listen(5000);

let bound = '----------boundary--------------';
let body = `--${bound}\r\n`;
    body += 'Content-Disposition: form-data; name="file"; filename="MyFile.txt"\r\n';
    body += 'Content-Type: text/plain\r\n\r\n';
    body += fs.readFileSync('MyFile.txt');
    body += `\r\n--${bound}--\r\n`;

let options = {
    host: 'localhost',
    path: '/',
    port: 5000,
    method: 'POST',
    headers: {
        'content-type':'multipart/form-data; boundary=' + bound
    }
};

let req = http.request(options, (res) => {
    let responseData = '';
    res.on('data', (chunk) => {
        console.log('data body:\n', responseData += chunk.toString('utf-8'));
    });
});

req.end(body);
