var http = require('http');

let h = (r) => {
    let rc = '';
    for (key in r.headers) 
        rc += `<h3> ${key}: ${r.headers[key]} </h3>`;
    return rc;
}

http.createServer(function (request, response){
    let b = '';
    request.on('data', str => {
        b += str;
        console.log('data', b);
    });
    response.writeHead(200, {'Content-Type' : 'text/html; charset = utf-8'})
    request.on('end', () => response.end(
                                            '<body>' +
                                            '<h1>Request structure</h1>' +
                                            `<h2>method: ${request.method} </h2>` +
                                            `<h2>uri: ${request.url} </h2>` +
                                            `<h2>version: ${request.httpVersion} </h2>` +
                                            `<h2>headers: ${h(request)} </h2>` +
                                            `<h2>body: ${b} </h2>` +
                                            `</body>`
    ))
}).listen(3000);

console.log('Server running at http://localhost:3000/')