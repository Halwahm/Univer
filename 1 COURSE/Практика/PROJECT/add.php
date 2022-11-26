
<head>
<link rel="stylesheet" href="./css/style_header.css">
<link rel="shortcut icon" href="./photos/169-1690130_speech-bubble-text-text-icon-black-and-white.png" type="image/png">
<style>
    .add_form{
        margin-top: 50px;
        margin-left: 30px;
    }

    #all {
        margin-top: 15px;
    }
</style>
</head>

<!-- header -->
<div class="header">
    <div class="header_section">
        <div class="header_item headerButton"><a href="index.php">Главная</a></div>
    </div>
</div>
<!-- --------------- -->


<?php
require_once 'database.php';
?>


<form action="create.php" method="post" class="add_form">
    <p id="all">Заголовок</p> <br/>
    <input type ="text" name="title">

    <p id="all">Пост-заголовок</p> <br/>
    <input type="text" name="post-title">

    <p id="all">Описание</p> <br/>
    <textarea name="description"></textarea> <br/>

    <p id="all">Прикрепить фото</p> <br/>
    <input type="file" name="src"> <br/> <br/>

    <p id="all">Прикрепить видео</p> <br/>
    <input type="file" name="video">

    <br> <br> <br> <br>

    <button type="submit">Добавить</button>
</form>