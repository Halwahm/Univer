var dino = document.getElementById("dino");
var cactus = document.getElementById("cactus");

document.addEventListener("keydown", function(event) {
    jump();
});

function jump() {
    if(dino.classList != "jump") {
        dino.classList.add("jump");
    }
    setTimeout(function() {
        dino.classList.remove("jump");
    }, 300);
}

let position = setInterval (function() {
let dinoTop = parseInt(window.getComputedStyle(dino).getPropertyValue("top")); //получение css свойств объекта; возваращает значение указанного свойства
let cactusLeft = parseInt(window.getComputedStyle(cactus).getPropertyValue("left"));

    if (cactusLeft < 50 && cactusLeft > 0 && dinoTop >= 140) {
        alert("GAME OVER");
    }
}, 10);