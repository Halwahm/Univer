const http = require('http');
const url = require('url');

http.createServer(function(request, response) {
    let data = '';
    request.on('data', (chunk) => { data += chunk; });
    request.on('end', () => {
        response.writeHead(200, {'Content-type': 'application/json; charset=utf-8'});
        data = JSON.parse(data);
        let jsonResponse = {};
        jsonResponse.__comment = 'Response: ' + data.__comment;
        jsonResponse.x_plus_y = data.x + data.y;
        jsonResponse.Concatenation_s_o = data.s + ' ' + data.o.surname + ' ' + data.o.name;
        jsonResponse.Length_m = data.m.length;

        response.end(JSON.stringify(jsonResponse));
    });
}).listen(5000);

let parameters = JSON.stringify({
    __comment: "Request",
    x: 1,
    y: 2,
    s: "task",
    m: [1, 2, 3],
    o: {
        surname:"aa",
        name: "bb"
    }
});
console.log(`params: ${parameters}`);
let path = `/`;

let options = {
    host: 'localhost',
    path: path,
    port: 5000,
    method: 'POST',
    headers: {
        'content-type' : 'appliation/json', 
        'accept' : 'application/json'
    }
};

let request = http.request(options, (res) => {
    console.log(`Response status:`, res.statusCode);

    let data= '';
    res.on('data', (chunk) => {
        data += chunk.toString('utf8');
    });
    res.on('end', () => {
         console.log(`body: ${data}`);
         console.log(`parsed:`, JSON.parse(data));
    })
});

request.end(parameters);
