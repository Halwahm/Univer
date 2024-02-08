//  Modules
const fs        = require("fs");
const pathname  = require("path");


class FileSender {
    
    constructor(fileName = "static/") {
        this.fileName = fileName.replace(/^\//g, '');
        this.fileExtension = pathname.extname(fileName);
    }

    GetHeaderByFileExtension = (fileExtension) => {
        let headersObject;

        switch (fileExtension) {
            case ".html":
                headersObject = {
                    "Content-Type": "text/html"
                };
                break;
            case ".css":
                headersObject = {
                    "Content-Type": "text/css"
                };
                break;
            case ".js":
                headersObject = {
                    "Content-Type": "text/javascript"
                };
                break;
            case ".png":
                headersObject = {
                    "Content-Type": "image/png"
                };
                break;
            case ".docx":
                headersObject = {
                    "Content-Type": "application/msword"
                };
                break;
            case ".json":
                headersObject = {
                    "Content-Type": "application/json"
                };
                break;
            case ".xml":
                headersObject = {
                    "Content-Type": "application/xml"
                };
                break;
            case ".mp4":
                headersObject = {
                    "Content-Type": "video/mp4"
                };
                break;
            default:
                headersObject = {
                    "Content-Type": "text/plain"
                };
                console.log("Error. Unacceptable file format.");
                break;
        }

        return headersObject;
    }

    WriteErrorResponse = (response, statusCode, statusMessage) => {
        response.statusCode     = statusCode;
        response.statusMessage  = statusMessage;
        response.end(`Error ${statusCode}. ${statusMessage}`); 
    }


    SendFile = (request, response) => {
        if (fs.existsSync(this.fileName)) {
            let file = fs.readFileSync(this.fileName);

            response.writeHead(200, this.GetHeaderByFileExtension(this.fileExtension));
            response.end(file);
        } else {
            this.WriteErrorResponse(response, 404, "File not found.",);
        }
    }
}

module.exports = (fileName) => new FileSender(fileName);