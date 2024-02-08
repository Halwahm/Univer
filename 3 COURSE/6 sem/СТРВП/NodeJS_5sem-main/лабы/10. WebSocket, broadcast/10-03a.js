const WebSocket = require('ws');
const ws = new WebSocket('ws://localhost:5000/broadcast');

let parm = process.argv[2];
let prfx = typeof parm == 'undefined' ? 'B' : parm;

console.log('parm2 = ', parm);

ws.on('open', () => {
    let k = 0;
    setInterval(() => { ws.send(`clientS: ${prfx}-${++k}`); }, 1000);

    ws.on('message', message => { console.log(`Received message => ${message}`) });

    setTimeout(() => { ws.close() }, 25000)
});