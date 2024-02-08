let udp = require('dgram');
const { Interface } = require('readline');
let WebSocket = require('ws');
const fs = require('fs');
//commandline
// let rl = Interface () {
//     in : process.stdin,
//     out : process.stdout
// }

let param = process.argv[2] ? process.argv[2] : 'name';

const readline = require('readline');
 const rl = readline.createInterface({
   input: process.stdin,
   output: process.stdout
 });

let name = 'curr';

 const ws = new WebSocket('ws://localhost:3000');
 ws.on('open', wss => {
    rl.on('line', (line) => {
        console.log(`Name: ${line}`);
        name = line;
        rl.close();
      });
     ws.onmessage = message => {
         console.log(`Server mes`, message.data);
     };
     setInterval(()=>{
         ws.send(`${param}: ${name}`);
     }, 3000)
     setInterval(()=>{
        ws.close();
    }, 30000)
 });



const wsss = new WebSocket('ws://localhost:4000');

wsss.on('open', () => {
    const duplex = WebSocket.createWebSocketStream(wsss, {encoding: 'utf8'});
    // duplex._write(wsss, {encoding: 'utf8'});
    // duplex.write('sd');
    let rfile = fs.createReadStream(`./b.txt`);
    rfile.pipe(duplex);
});