var http = require('http');
var url = require('url');
var fs = require('fs');

function factorial(k) {
    if (k <= 1) return 1;
    return k * factorial(k - 1);
}

http.createServer((request, response) => {
    let path = url.parse(request.url).pathname;
    if (path == '/fact') {
        console.log(request.url);
        let query = url.parse(request.url, true).query;
        if (query.k != null) {
            let k = parseInt(query.k);
            if (k == null) {
                return;
            }
            response.writeHead(200, { 'Content-type': 'application/json' });
            response.end(JSON.stringify({'k': k, 'fact': factorial(k)}));
        }
    } else if (path == '/') {
        let html = fs.readFileSync('./fact.html');
        response.writeHead(200, {'Content-type': 'text/html'});
        response.end(html);
    }
}).listen(3000);

console.log('Server running on http://localhost:3000');