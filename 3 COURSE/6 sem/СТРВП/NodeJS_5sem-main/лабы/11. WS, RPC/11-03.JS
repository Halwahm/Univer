const WebSocket = require('ws');
const wss = new WebSocket.Server({port:4000, host:'localhost'});

let k = 0;

wss.on('connection', (ws) => {

    setInterval(() => {
        console.log('server: ping');
        ws.ping(`11-03-server: ${++k}`)
    }, 15000);

    setInterval(() => {
        console.log(wss.clients.size);
    }, 5000);
    
    ws.on('pong', (data)=>{
        console.log('on pong: ', data.toString());
    });
});

wss.on('error', (e) => { console.log('error ', e) });

