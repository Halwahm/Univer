<?php

include("database.php");

$new_name = $_POST["name"];
$new_email = $_POST["email"];
$new_message = $_POST["message"];

mysqli_query($db, "INSERT INTO `information from form` (`id`, `Name`, `Email`, `Message`) VALUES (NULL, '$new_name', '$new_email', '$new_message');")

?>