const emailModule = require('m05_han');

async function main() {
    let from = 'halaleenko1325476@yandex.ru';
    let to = 'halaleenko1325476@yandex.ru';
    let pass = 'qaeqafmgeoejhzke';
    let message = 'Hello from 05-04!';
  
    try {
      await emailModule.send(from, to, pass, message);
      console.log('Функция send успешно выполнена');
    } catch (error) {
      console.error('Произошла ошибка при выполнении функции send:', error);
    }
}
  
main();