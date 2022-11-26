<title>HM news</title>

<link rel="stylesheet" href="./css/style_header.css">
<link rel="shortcut icon" href="./photos/169-1690130_speech-bubble-text-text-icon-black-and-white.png" type="image/png">
<link rel="stylesheet" href="./css/txt1.css">
<link rel="stylesheet" href="./css/footer.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" 
    integrity="sha512-9usAa10IRO0HhonpyAIVpjrylPvoDwiPUiKdWk5t3PyolY1cOd4DSE0Ga+ri4AuTroPR5aQvXU9xC6qOPnzFeg==" 
    crossorigin="anonymous" referrerpolicy="no-referrer"/>

<!-- header -->
<div class="header">
        <div class="header_section">
            <div class="header_item headerButton"><a href="index.php">Главная</a></div>
        </div>
    </div>
<!-- ------------ -->
<?php 
require_once "functions.php";
$post = get_posts_by_id($new_id);
?>

<h2> <?=$post['title']?> </h2>
<img src="./photos/<?=$post['src_name']?>">
<h1></h1>
<p> <?=$post['full_text']?> </p>

<video controls class="video">
    <source src="./videos/<?=$post['video_name']?>" type="video/mp4">
</video>

<!-- ------------------------------------ -->
<footer id="footer_main">
    <section class="footer">
        <div class="social">
            <a href="https://www.instagram.com/halwa_hm/"><i class="fab fa-instagram"></i></a>
            <a href="https://vk.com/id318776403"><i class="fab fa-vk"></i></a>
            <a href="http://tiktok.com/@daprostohalwa"><i class="fab fa-tiktok"></i></a>
        </div>
        <div class="copyright">
            @Halwa_hm 2022
        </div>    
    </section>
</footer>