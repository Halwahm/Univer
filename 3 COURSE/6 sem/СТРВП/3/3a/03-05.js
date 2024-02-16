const http = require("http");
const url = require("url");

const host = 'localhost';
const port = 5000;

function factorial(n, callback) {
    if (n === 0) {
        setImmediate(() => callback(null, 1));
    } else {
        setImmediate(() => {
            factorial(n - 1, (err, result) => {
                if (err) {
                    callback(err);
                } else {
                    callback(null, n * result);
                }
            });
        });
    }
}

const server = http.createServer(async (request, response) => {
    if (request.url.startsWith('/fact')) {
        const myUrl = new URL(`http://${host}:${port}` + request.url);
        let k = parseInt(myUrl.searchParams.get('k'));
        
        let startTime = process.hrtime();

        factorial(k, (err, result) => {
            if (err) {
                response.statusCode = 500;
                response.end(`Error: ${err.message}`);
            } else {
                let elapsedTime = process.hrtime(startTime);
                let elapsedTimeMs = elapsedTime[0] * 1000 + elapsedTime[1] / 1000000;
                response.writeHead(200, {'Content-Type': 'text/json'});
                response.end(JSON.stringify({k: k, fact: result, elapsedTimeMs: elapsedTimeMs}));
            }
        });
    } else {
        response.writeHead(404);
        response.end('Not found');
    }
});

server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}/fact?k=5`);
});