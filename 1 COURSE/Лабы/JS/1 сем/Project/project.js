$(document).ready( ()=> {

var signs = [
    '7', '8', '9', '+',
    '4', '5', '6', '-',
    '1', '2', '3', '/',
    '0', '.', '=', '*', 'c'
];

// форма калькулятора
var calc = document.getElementById('calc');
var textArea = document.getElementById('inputVal');

// Добавление кнопок к форме калькулятора
signs.forEach(function (sign) { //перебор всех элементов массива
    var signElement = document.createElement('div');
    signElement.className = 'btn';
    signElement.innerHTML = sign;
    calc.appendChild(signElement); //добавляем узел в качестве последнего дочернего узла в указанный родительский элемент
});

// проходим по всем кнопкам калькулятора, добавляем обработчик на клик
document.querySelectorAll('#calc-wrap .btn').forEach(function (button) {
    // Добавляем действие, выполняемое при клике на любую кнопку
    button.addEventListener('click', onButtonClick); //присоединяем обработчик события к определенному элементу
});

function onButtonClick(event) {
    if (event.target.innerHTML === 'c') {
        textArea.innerHTML = '0';
    } else if (event.target.innerHTML === '=') {
        // Если нажата кнопка "=", то, приведя выражение в текстовом поле в javascript, вычислить значение
        textArea.innerHTML = eval(textArea.innerHTML);
    } else if (textArea.innerHTML === '0') {
        // Если textarea содержит только "0", то стереть "0" и записать значения кнопки в текстовое поле
        textArea.innerHTML = event.target.innerHTML;
    } else {
        // Добавление значения кнопки в текстовое поле
        textArea.innerHTML += event.target.innerHTML;
    }
}
});

    // TIME
    window.onload = function(){
        window.setInterval(function(){
            let now = new Date();
            let clock = document.getElementById("clock");
            clock.innerHTML = now.toLocaleTimeString();
        }, 10);
    };  
