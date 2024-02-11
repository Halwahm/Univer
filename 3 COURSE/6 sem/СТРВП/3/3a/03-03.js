const http = require("http");
const url = require("url");

const host = 'localhost';
const port = 5000;

function Factorial(k) {
    if (k < 3) return k;
    else return k * Factorial(k - 1);
}

const server = http.createServer((request, response) => {
    if (request.url.startsWith('/fact')) {
        const myUrl = new URL(`http://${host}:${port}` + request.url);
        let k = parseInt(myUrl.searchParams.get('k'));
        let fact = Factorial(k);
        let htmlResponse = `
            <html lang="en">
            <head>
                <title>Factorial Results</title>
                <meta charset="UTF-8">
            </head>
            <body>
                <h1>k=${k}</h1>
                <ul id="results"></ul>
                <script>
                    let resultsList = document.getElementById('results');
                    let startTime = performance.now();
                    `;
        
        // Adding fetch requests in a loop
        for (let x = k; x < k + 20; x++) {
            htmlResponse += `
                fetch('http://${host}:${port}/fact?k=${x}')
                    .then(response => response.text())
                    .then(data => {
                        let elapsedTime = performance.now() - startTime;
                        let factResult = ${Factorial(x)};
                        resultsList.innerHTML += '<li>${x}. Результат: ' + elapsedTime.toFixed(2) + 'ms - ${x} / ' + factResult + '</li>';
                    });
            `;
        }
        
        htmlResponse += `
                </script>
            </body>
            </html>
        `;
        
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(htmlResponse);
    } else {
        response.writeHead(404);
        response.end('Not found');
    }
});

server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}/fact?k=5`);
});
