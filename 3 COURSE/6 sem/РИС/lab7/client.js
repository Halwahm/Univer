const dgram = require('dgram');
const client = dgram.createSocket('udp4');

client.on('message',message => {
    console.log('Received time: ' + message.toString());
});

client.send('time', 5555, '127.0.0.1');
