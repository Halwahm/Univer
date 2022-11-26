<?php

require_once "database.php";

function get_news() {
    global $db;
    $sql = "SELECT * FROM `news`";
    $result = mysqli_query($db, $sql);
    $news = mysqli_fetch_all($result, MYSQLI_ASSOC); //получение всех строк и преобразование в массив
    return $news;
}

function get_posts_by_id() {
    $news_id = $_GET['new_id'];
    global $db;
    $sql = "SELECT * FROM `news` WHERE id = ".$news_id;
    $result = mysqli_query($db, $sql);
    $post = mysqli_fetch_assoc($result);
    return $post;
}
?>