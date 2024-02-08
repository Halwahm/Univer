const http = require('http');
const parseString = require('xml2js').parseString;
const xmlbuilder = require('xmlbuilder');

http.createServer(function(req, res) {
    let data = '';
    req.on('data', (chunk) => { data += chunk; });
    req.on('end', () => {
        res.writeHead(200, {'Content-type': 'text/xml'});
        parseString(data, function(err, result) {
            let xSum = 0;
            let mSum = '';
            result.request.x.forEach((p) => {
                xSum += parseInt(p.$.value);
            });
            result.request.m.forEach((p) => {
                mSum += p.$.value;
            });
            console.log(mSum);
            let xmlDoc = xmlbuilder.create('response').att('id', '67');
            xmlDoc.ele('sum').att('result', xSum).up().ele('concat').att('result', mSum);
            res.end(xmlDoc.toString({ pretty: true }));
        });
    });
}).listen(5000);

let parameters = xmlbuilder.create('request').att('id', '28');
parameters.ele('x').att('value', '1').up()
          .ele('x').att('value', '2').up()
          .ele('m').att('value', 'a').up()
          .ele('m').att('value', 'b').up()
          .ele('m').att('value', 'c').up();

let options = {
    host: 'localhost',
    path: '/',
    port: 5000,
    method: 'POST',
    headers: {
        'content-type':'text/xml', 
        'accept':'text/xml'
    }
};

let req = http.request(options, (res) => {
    console.log('status code:', res.statusCode);

    let responseData = '';
    res.on('data', (chunk) => {
        responseData += chunk;
    });
    res.on('end', () => {
        console.log('body=', responseData);
            parseString(responseData, (err, str) => {
                if(err) {
                 console.log('xml parser error');
                }
                else {
                 console.log('sum = ', str.response.sum[0].$.result);
                 console.log('concat = ', str.response.concat[0].$.result);
                }
            });
    });
});
req.end(parameters.toString({pretty:true}));