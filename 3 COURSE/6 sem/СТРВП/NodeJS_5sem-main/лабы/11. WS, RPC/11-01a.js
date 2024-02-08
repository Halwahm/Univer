const fs = require('fs');
const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000');

ws.on('open', ()=>{
    const duplex = WebSocket.createWebSocketStream(ws, {encoding: 'utf8'});
    let rfile = fs.createReadStream(`./File.txt`);
    rfile.pipe(duplex);
});