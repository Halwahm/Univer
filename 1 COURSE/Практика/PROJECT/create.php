<?php 
require_once 'database.php';

$title = $_POST['title'];
$description = $_POST['description'];
$intro_text = $_POST['post-title'];
$src = $_POST['src'];
$video = $_POST['video'];

mysqli_query($db, "INSERT INTO `news` (`id`, `title`, `intro_text`, `full_text`, `src_name`, `video_name`) VALUES (NULL, '$title', '$intro_text', '$description', '$src', '$video')");

header("location:index.php");
?>