const rpcWSC = require('rpc-websockets').Client;
const readline = require('readline');

let ws = new rpcWSC('ws://localhost:4000/');

let read = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

ws.on('open', () => {
    console.log('Enter notify A, B or C');
    read.on('line', function(line) {
        ws.notify(line);
    });
});
