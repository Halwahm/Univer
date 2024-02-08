const WebSocket = require('ws');

let k = 1;
let socket = new WebSocket('ws:/localhost:4000/wsserver');
socket.onopen = () => {
    console.log('socket.onopen');
    setInterval(() => { socket.send(`10-02 client: ${k++}`); },3000);
    setTimeout(function() {
        socket.close();
    }, 25000);
};

socket.onclose = (e) => { console.log('socket.onclose', e); };
socket.onmessage = (e) => { console.log('socket.onmessage', e.data); };
socket.onerror = function(error) { console.log('Error: ' + error.message); };
