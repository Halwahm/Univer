const rpc = require('rpc-websockets').Client;
const eventSocket = new rpc('ws://localhost:4000');

eventSocket.on('open', () => {
    eventSocket.subscribe('C');
    eventSocket.on('C', (p) => console.log(p, 'It is C event!\n'));
});