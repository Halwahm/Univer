//Api express
const express = require('express');
const path = require('path');
const cors = require('cors');
require('dotenv').config();
const errorHandler = require('./middleware/ErrorHandlingMiddleware');
const Route = require('./Route/indexRoute');
const fileUpload = require('express-fileupload');
const feedback = require('./Model/feedback');
const fs = require('fs');



const app = express();

// const options = {
//     key: fs.readFileSync('localhost.key'),
//     cert: fs.readFileSync('localhost.crt')
//     };
const http = require('http').createServer(app);
const io = require("socket.io")( http, {
    cors: {
      origin: "http://localhost:3000",
      methods: ["GET", "POST"]
    }
  });

// Обработка соединения сокета
io.on('connection', (socket) => {
    console.log('a user connected');

    socket.on('disconnect', () => {
        console.log('user disconnected');
    });

    // Обработка сообщения от клиента
    socket.on('message', (msg) => {
        console.log('message: ' + msg);
        feedback.addFeedback(msg.id, msg.id_Book, msg.raiting, msg.text).then((res) => {
            console.log(res);
            io.emit('message', res);
        });
    });
});


//Подключение cors
app.use(cors());
//Парсинг json
app.use(express.json());
app.use(fileUpload());
app.use(express.static(path.resolve(__dirname, 'public/static')));
//Парсинг urlencoded
app.use(express.urlencoded({ extended: true }));
//Подключение роутов
app.use('/api', Route);

//Обработка ошибок
app.use(errorHandler);
//Запуск сервера
const PORT = process.env.PORT;
http.listen(PORT, () => {
    console.log(`Server started on port ${PORT}`);
});


