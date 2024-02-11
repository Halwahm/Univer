const http = require("http");
const fs = require("fs");
const readline = require('readline');
const { stdin: input, stdout: output } = require('process');
const rl = readline.createInterface({ input, output });

const host = 'localhost';
const port = 5000;

let state = "norm";
let acceptableStates = ['norm', 'idle', 'stop', 'test'];

const server = http.createServer((request, response) => {
    response.writeHead(200, { 'Content-Type': 'text/html' });

    const htmlContent = `
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Current State</title>
        </head>
        <body>
            <h1>${state}</h1>
        </body>
        </html>
    `;

    response.end(htmlContent);
});

server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
    rl.setPrompt("new state>")
    rl.prompt(true);
    rl.on('line', (newState) => {
        if (newState === 'exit') {
            process.exit();
        }
        if (acceptableStates.indexOf(newState) === -1) {
            console.log('Unacceptable state');
        }
        else {
            state = newState;
            console.log(`Current state is ${state}`);
        }
    });
});
