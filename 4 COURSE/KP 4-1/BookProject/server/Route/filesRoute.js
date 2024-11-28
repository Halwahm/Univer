const ApiError = require('../error/ApiError');

const Route = require('express').Router();

Route.post('/upload', (req, res) => {
  const { name } = req.body;
    if (!req.files || Object.keys(req.files).length === 0) {
        return res.status(400).send('Файл не выбран');
      }
    
      const file = req.files.file;
      const fileName = name;
    
      file.mv(`${__dirname}/../public/static/${name}`, err => {
        if (err) {
          console.log(err);
          return res.status(500).send('Ошибка при загрузке файла');
        }
    
        res.json({ fileName: fileName, filePath: `/static/${name}` });
      });
});

module.exports = Route;