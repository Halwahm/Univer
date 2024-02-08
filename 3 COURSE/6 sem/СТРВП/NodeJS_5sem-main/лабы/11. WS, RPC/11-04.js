const WebSocket = require('ws');
const wss = new WebSocket.Server({port:4000, host:'localhost'});

let count_of_messages = 0;

wss.on('connection', (ws)=>{
    let data0;
    ws.on('message', (data)=>{
        data0 =  JSON.parse(data);
        console.log('on message: ', data0);
    });

    setInterval(()=> {ws.send(JSON.stringify({server: count_of_messages++, client: data0.x, timestamp: new Date().toISOString()}))}, 5000);
});

wss.on('error', (e)=>{console.log('wss server error', e)});
