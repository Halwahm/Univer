const rpc = require('rpc-websockets').Client;
const eventSocket = new rpc('ws://localhost:4000');

eventSocket.on('open', () => {
    eventSocket.subscribe('A');
    eventSocket.on('A', (p) => console.log(p, 'It is A event!\n'));
});