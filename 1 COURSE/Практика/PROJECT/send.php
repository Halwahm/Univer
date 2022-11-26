<?php
$to = "halaleenko1325476@gmail.com";
$tema = "Форма обратной связи";
$message = "Ваше имя: ".$_POST['name']."<br>";
  $message .= "E-mail: ".$_POST['email']."<br>"; 
$message .= "Сообщение: ".$_POST['message']."<br>";
$headers  = 'MIME-Version: 1.0' . "\r\n"; // заголовок соответствует формату плюс символ перевода строки
  $headers .= 'Content-type: text/html; charset=utf-8' . "\r\n"; // указывает на тип посылаемого контента
mail($to, $tema, $message, $headers); //отправляет получателю на емайл значения переменных

include("into_db.php");
header("location:index.php");
?>

