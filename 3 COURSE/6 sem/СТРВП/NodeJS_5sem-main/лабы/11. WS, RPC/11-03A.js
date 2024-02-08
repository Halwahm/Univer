const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000');

ws.on('ping', (data)=>{
    console.log('on ping: ', data.toString());
    ws.pong(data);
});

// ws.on('message', data => {
//     console.log(data);
// });

setInterval(() => {
    console.log('server: ping');
    //ws.ping('client ping')
}, 5000);
