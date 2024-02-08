const http      = require("http");
const fs        = require("fs");
var FileSender  = require("../m07-01/filesender");


http.createServer((request, response) => {
    const myURL = new URL(
        request.url,
        `http://${request.headers.host}/`
    );

    if (myURL.pathname === "/") {
        let html = fs.readFileSync("index.html");
        
        response.writeHead(200, { "Content-Type": "text/html" });
        response.end(html);
    } else if (request.method === 'GET') {
        if (myURL.pathname.includes("static")) {
            let fileSender = FileSender(myURL.pathname);
            fileSender.SendFile(request, response);
        }
    } else {
        response.statusCode = 405;
        response.statusMessage = "Invalid request method.";
        response.end("Error 405. Invalid request method.");
    }
}).listen(5000);

console.log("Server is now running at http://localhost:5000");