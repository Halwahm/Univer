// генерация случайных чисел
function getRandomNumbers() {

    const array = new Uint8Array(1);

    for (let i = 0; i < 5; ++i) {
        document.write(crypto.getRandomValues(array) + '<br>');
    }

}
