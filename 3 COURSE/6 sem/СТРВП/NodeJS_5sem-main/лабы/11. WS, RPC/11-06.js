const rpcServer = require('rpc-websockets').Server;
const readline = require('readline');

let read = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
const eventSocket = new rpcServer({ port: 4000, host: 'localhost'});

eventSocket.event('A');
eventSocket.event('B');
eventSocket.event('C');

setInterval(()=> eventSocket.emit('A', {n:'hi'}), 1000)
setInterval(()=> eventSocket.emit('B', {n:'hi'}), 1000)
setInterval(()=> eventSocket.emit('C', {n:'hi'}), 1000)
//консоль

console.log('Enter smth');
read.on('line', function(line) {
    eventSocket.emit(line, console.log('emited', line));
});
