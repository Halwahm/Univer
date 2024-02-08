var http = require('http');
const fs = require('fs');
const url = require('url');
const pathToFile = './file/StudentList.json';

function readFile() {
    try {
        // fs.accessSync(pathToFile);
        stats = fs.lstatSync(pathToFile);
        if (stats.isDirectory()) {
            process.stderr.write(
                'ERROR: It is not file!\n'
            );
            process.exit(1);
        }

        return fs.readFileSync(pathToFile).toString();
        
    } catch (e) {
        process.stderr.write(
            'ERROR: File not exist'
        );

        process.exit(1);
    }
}

http.createServer((request, response) => {
    let path = url.parse(request.url).pathname;
    if (/\/\d+/.test(path)) {
        let fileJSON = readFile();
        let id = Number(path.match(/\d+/)[0]);
        JSON.parse(fileJSON).forEach(item => {
            if(item.id === id) {
                response.setHeader('Content-Type', 'application/json');
                response.write(JSON.stringify(item));
            }
        });
        if(!response.hasHeader('Content-Type')) {
            errorHandler(request, response, 1, ` id ${id} doesnt exist`);
        }
        response.end();
    }
    else if ('/' == path && url.parse(request.url, true).query.id) {
        console.log('here');
        let id = url.parse(request.url, true).query.id;
        if(url.parse(request.url, true).query.id) {
            let fileJSON = readFile();
            JSON.parse(fileJSON).forEach(item => {
                if(item.id === Number.parseInt(id)) {
                    response.setHeader('Content-Type', 'application/json');
                    response.write(JSON.stringify(item));
                }
            });
            if(!response.hasHeader('Content-Type')) {
                errorHandler(request, response, 1, ` id ${id} doesnt exist`);
            }
            response.end();
        }
    else{
        if(!response.hasHeader('Content-Type')) {
            errorHandler(request, response, 1, ` invalid request`);
        }
}
}

}).listen(8080);

console.log('Server running at http://localhost:8080/');

function errorHandler (request, response, code, message)  {
    response.writeHead(500, {'Content-Type': 'application/json; charset=utf-8'});
    response.end(`{"error": "${code}", "message": "${message}"}`);
};
