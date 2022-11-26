$(document).ready( ()=> {

$("#txt1").click(function(){
    $(this).html('<img src = "kasper.jpg" style = "height: 400px; width: 300px;">');
});
});

    function table(){

        document.write("<table border = 10>");
        document.write("<th>свойство</th>");
        document.write("<th>значение</th>");
        document.write("<tr><td>1. всю информацию о браузере пользователя</td><td>"+navigator.userAgent+"</td></tr>");
        document.write("<tr><td>2. версию браузера</td><td>"+navigator.appVersion+"</td></tr>");
        document.write("<tr><td>3. назване браузера</td><td>"+navigator.appName+"</td></tr>");
        document.write("<tr><td>4. кодовое название браузера</td><td>"+navigator.appCodeName+"</td></tr>");
        document.write("<tr><td>5. ОС, которую использует пользователь</td><td>"+navigator.platform+"</td></tr>");
        document.write("<tr><td>6. включена ли поддержка Java в браузере</td><td>"+navigator.javaEnabled()+"</td></tr>");
        document.write("<tr><td>7. ширину и высоту экрана</td><td>ширина экрана: "+screen.width+", высота экрана: "+screen.height+"</td></tr>");
        document.write("<tr><td>8. глубину цвета</td><td>"+screen.colorDepth+"</td></tr>");
        document.write("<tr><td>9. URL, которые были посещены в данном окне браузера</td><td>"+history+"</td></tr>");
        document.write("<tr><td>10. URL текущего документа</td><td>"+location.href+"</td></tr>");
        document.write("<tr><td>11. путь к загруженному документу</td><td>"+location.pathname+"</td></tr>");
        document.write("<tr><td>12. имя домена загруженного документа</td><td>"+location.host+"</td></tr>");
        }

        // TIME
    window.onload = function(){ //загрузка ресурсов
        window.setInterval(function(){
            let now = new Date();
            let clock = document.getElementById("clock");
            clock.innerHTML = now.toLocaleTimeString(); //использование функционала ОС
        }, 10);
    };