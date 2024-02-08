let udp = require('dgram');
let stream = require('stream');
let ws = require('ws');
const fs = require('fs');

const wss = new ws.WebSocketServer({
    port: 3000
});

wss.on('connection', client => {
    
    console.log('client connected')


    client.on('message', message => {
        console.log(message.toString())
        wss.clients.forEach((cl)=>{cl.send(message.toString())})
    })
    client.on('close', () => {
        console.log('close');
    })
})


const wsss = new ws.WebSocket.Server({port: 4000, host: 'localhost'});

wsss.on('connection', client => {
    const duplex = ws.WebSocket.createWebSocketStream(client, {encoding: 'utf8'});
    let wfile = fs.WriteStream('a.txt');
    duplex.pipe(wfile);
})