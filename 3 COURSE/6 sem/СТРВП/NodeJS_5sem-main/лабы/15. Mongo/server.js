const http      = require('http');
const url       = require('url');
const mongoose  = require('mongoose');

const uri = 'mongodb+srv://Kora:12345@cluster0.r0fvn.mongodb.net/BSTU?retryWrites=true&w=majority';

mongoose.connect(uri, (error) => {
    if (error) {
        console.log('Connection error: ', error.message);
    }
    else {
        console.log('Connected to mongodb');
    }
});

const FacultyModel = require('./schemas/faculty');
const PulpitModel = require('./schemas/pulpit');

function get_handler(request, response) {
    switch (request.url) {
        case '/api/faculties':
            FacultyModel.find({}).lean()
            .then(data => {
                sendResponseSuccessJSON(response, data);
            })
            .catch(error => sendResponseErrorJSON(response, 400, error));
            break;
        case '/api/pulpits':
            PulpitModel.find({}).lean()
            .then(data => {
                sendResponseSuccessJSON(response, data);
            })
            .catch(error => sendResponseErrorJSON(response, 400, error));
            break; 
        default:
            break;
    }
}

function post_handler(request, response) {
    let data = '';
    switch (request.url) {
        case '/api/faculties':
            request.on('data', (chunk) => {
                data += chunk;
            });

            request.on('end', () => {
                data = JSON.parse(data);
                
                let faculty = new FacultyModel(data);
    
                faculty.save()
                .then(doc => {
                    sendResponseSuccessJSON(response, data);
                })
                .catch(error => sendResponseErrorJSON(response, 400, error));
            });
            break;
        case '/api/pulpits':
            request.on('data', (chunk) => {
                data += chunk;
            });

            request.on('end', () => {
                data = JSON.parse(data);
                
                let pulpit = new PulpitModel(data);
    
                pulpit.save()
                .then(doc => {
                    sendResponseSuccessJSON(response, data);
                })
                .catch(error => sendResponseErrorJSON(response, 400, error));
            });
            break; 
        default:
            break;
    }
}

function put_handler(request, response) {
    let data = '';
    switch (request.url) {
        case '/api/faculties':
            request.on('data', (chunk) => {
                data += chunk;
            });

            request.on('end', () => {
                data = JSON.parse(data);
                FacultyModel.find({faculty: data.faculty}).lean()
                .then(datal => {
                    if  (datal.length == 0) throw "no such faculty"
                    else     FacultyModel.updateOne({ faculty: data.faculty }, { faculty_name: data.faculty_name })
                    .then(doc => {
                        sendResponseSuccessJSON(response, data);
                    })
                    .catch(error => sendResponseErrorJSON(response, 400, error));
                })
                .catch(error => sendResponseErrorJSON(response, 400, error));

            });
            break;
        case '/api/pulpits':
            request.on('data', (chunk) => {
                data += chunk;
            });

            request.on('end', () => {
                data = JSON.parse(data);
                PulpitModel.find({pulpit: data.pulpit}).lean()
                    .then(datal => {
                        if (datal.length == 0) throw "no such pulpit"
                        else
                        PulpitModel.updateOne({ pulpit: data.pulpit }, { pulpit_name: data.pulpit_name })
                        .then(doc => {
                            sendResponseSuccessJSON(response, data);
                        })
                        .catch(error => sendResponseErrorJSON(response, 400, error));
                 })
                .catch((error) => sendResponseErrorJSON(response, 400, error));

            });
            break; 
        default:
            break;
    }
}

function delete_handler(request, response) {
    let path = decodeURI(url.parse(request.url).pathname);
    let pathElements = path.split('/');

    switch ('/api/' + pathElements[2]) {
        case '/api/faculties':
            FacultyModel.find({faculty: pathElements[3]}).lean()
            .then(datal => {
                if  (datal.length == 0) throw "no such faculty"
                else     
                FacultyModel.deleteOne({faculty: pathElements[3]})
                .then(data => {
                    sendResponseSuccessJSON(response, datal);
                })
                .catch(error => sendResponseErrorJSON(response, 400, error));
            })
            .catch(error => sendResponseErrorJSON(response, 400, error));

            break;
        case '/api/pulpits':
            PulpitModel.find({pulpit: pathElements[3]}).lean()
            .then(datal => {
                if (datal.length == 0) throw "no such pulpit"
                else
                    PulpitModel.deleteOne({pulpit: pathElements[3]})
                    .then(data => {
                        sendResponseSuccessJSON(response, datal);
                    }).catch(error => sendResponseErrorJSON(response, 400, error));
         })
        .catch((error) => sendResponseErrorJSON(response, 400, error));
            break; 
        default:
            break;
    }
}

function sendResponseSuccessJSON(response = new http.ServerResponse(), data) {
    response.writeHead(200, {'Content-Type': 'application/json'});
    response.end(JSON.stringify(data));
}

function sendResponseErrorJSON(response, statusCode, error) {
    response.statusCode = statusCode;
    response.end(JSON.stringify({message: error}));
}

http.createServer((request, response) => {
    switch (request.method) {
        case 'GET':
            get_handler(request, response);
            break;
        case 'POST':
            post_handler(request, response);
            break;
        case 'PUT':
            put_handler(request, response);
            break;
        case 'DELETE':
            delete_handler(request, response);
            break;    
        default:
            break;
    }
}).listen(3000);

console.log('Server is now running at http://localhost:3000');
