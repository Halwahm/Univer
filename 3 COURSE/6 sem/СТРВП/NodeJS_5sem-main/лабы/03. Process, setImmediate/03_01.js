let http = require('http'); 
let url = require('url');
let fs = require('fs');

let factorial = (n) => {
    return (n < 2 ? n : n * factorial(n - 1));
}

function Fact(n, cb) {
    this.fn = n;
    this.ffact = factorial;
    this.fcb = cb;
    this.calc = ()=>{process.nextTick(()=>{this.fcb(null, this.ffact(this.fn));});}
}
function Fac(n, cb) {
    this.fn = n;
    this.ffact = factorial;
    this.fcb = cb;
    this.calculate = ()=> {setImmediate(()=>{this.fcb(null, this.ffact(this.fn));})};
}

http.createServer(function (request, response){

    switch (request.url) {
        case '/':
            response.writeHead(200, {'Content-Type': 'text/html'});
            response.end(`<h1>${state}</h1>`);
            break;
        case '/f':
            response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8' });
            response.end(fs.readFileSync('./index.html'));
      break;
        default:
            let rc = JSON.stringify({ k: 0})
            if (url.parse(request.url).pathname === '/fact')
            {
                if (typeof(url.parse(request.url, true).query.k) != "undefined"){
                    let k = parseInt(url.parse(request.url, true).query.k)
                    if (Number.isInteger(k)){
                    response.writeHead(200, {'Content-Type': 'application/json; charset = utf-8', "Access-Control-Allow-Origin": "*" });
                    response.end(JSON.stringify({ 'k':k, 'fact': factorial(k)}));
                    }
                }
                else {
        
                    response.end(rc);
                }
            } 
            if (url.parse(request.url).pathname === '/fact4')
            {
                if (typeof(url.parse(request.url, true).query.k) != "undefined"){
                    let k = parseInt(url.parse(request.url, true).query.k)
                    if (Number.isInteger(k)){
                    response.writeHead(200, {'Content-Type': 'application/json; charset = utf-8', "Access-Control-Allow-Origin": "*" });
                    let fac = new Fact(k, (err, result) => {response.end(JSON.stringify({ 'k':k, 'fact': result})); })
                    fac.calc();
                    }
                }
                else {
        
                    response.end(rc);
                }
            } 
            if (url.parse(request.url).pathname === '/fact5')
            {
                if (typeof(url.parse(request.url, true).query.k) != "undefined"){
                    let k = parseInt(url.parse(request.url, true).query.k)
                    if (Number.isInteger(k)){
                    response.writeHead(200, {'Content-Type': 'application/json; charset = utf-8', "Access-Control-Allow-Origin": "*" });
                    let fac = new Fac(k, (err, result) => {response.end(JSON.stringify({ 'k':k, 'fact': result})); })
                    fac.calculate();
                    }
                }
                else {
        
                    response.end(rc);
                }
            }    
    }
   


}).listen(5000);
console.log('Server running at http://localhost:5000/');


let state = 'norm'
let buf = ""
process.stdin.setEncoding('utf-8');
process.stdout.write(`${state} -> `);
process.stdin.on('readable', () => {
  let chunk = null;
  while ((chunk = process.stdin.read()) != null) {
    if (chunk.trim().charCodeAt()) buf += chunk.trim()
    else
    {
        if (buf == 'exit') process.exit(0);
        else if (buf == 'norm' || buf == 'test' || buf == 'stop' || buf == 'idle') {
            process.stdout.write(`reg = ${state} -> ${buf}\n`);
            state = buf
        } else process.stdout.write('Unknow comand: ' + buf + '\n');
    buf=""
    process.stdout.write(`${state} -> `);
}
  }
});
