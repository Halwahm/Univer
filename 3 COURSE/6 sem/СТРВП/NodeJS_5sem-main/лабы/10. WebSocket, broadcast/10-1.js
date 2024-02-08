let http = require('http')
let WebS = require('ws')
let fs = require('fs')

let httpserver = http.createServer(function(req, res) {
    if (req.url == '/start') {
        res.writeHead(200, {'Content-type': 'text/html'});
        fs.readFile('10-1.html', (err, data) => {
            res.end(data);
        });
    } else {
        res.writeHead(400, {'Content-type': 'text/plain'});
        res.end('400 error');
    }
})
httpserver.listen(3000)

let wsserver = new  WebS.Server({port: 4000, host:'localhost', path: '/wsserver'})
wsserver.on('connection', (ws) => {
    let n = 0;
    let k = 1;
    ws.on('message', message => {
        console.log(message.slice(-1));
        console.log(parseInt(message.slice(-1)));
        n = parseInt(message.slice(-1));
    });

    setInterval(function(){
        ws.send(`10-01-server: ${n}->${k++}`);
    }, 5000);
})