<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>HM news</title>

    <link rel="shortcut icon" href="./photos/169-1690130_speech-bubble-text-text-icon-black-and-white.png" type="image/png">

    <script src="http://code.jquery.com/jquery-1.11.1.min.js"></script>
    <script src="http://cdn.jsdelivr.net/momentjs/2.8.4/moment.min.js"></script>

    <script src="script.js"></script>

    <link rel="stylesheet" href="./css/comment.css">
    <link rel="stylesheet" href="./css/time.css">
    <link rel="stylesheet" href="./css/index.css">
    <link rel="stylesheet" href="./css/style_header.css">
    <link rel="stylesheet" href="./css/footer.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css" 
    integrity="sha512-9usAa10IRO0HhonpyAIVpjrylPvoDwiPUiKdWk5t3PyolY1cOd4DSE0Ga+ri4AuTroPR5aQvXU9xC6qOPnzFeg==" 
    crossorigin="anonymous" referrerpolicy="no-referrer"/>
</head>

<body>

<!-- header -->
    <div class="header">
        <div class="header_section">
            <div class="header_item headerButton"><a href="#about">О нас</a></div>
            <div class="header_item headerButton"><a href="#form">Связь</a></div>
            <div class="header_item headerButton"><a href="add.php">Добавить статью</a></div>
        </div>
    </div>

<!--date-time --------------- -->
    
    <div class="today">
        <span>Сегодня:</span>
        <span class="date">
        <script>
            document.write(date+" ");
            document.write(thismonth+ " "+thisyear+" "+"года"+" — "+ DayofWeek);
        </script>
        (<span id="clockdat"></span>)
        </span>
    </div>

<!-- news -->
    
    <div class="post-wrap">
        <?php
        require_once "functions.php";
        $news = get_news();
        foreach($news as $new) {
            echo('
            <div class="post-item">
                <div class="post-item-wrap">
                ');
                ?>
            <a href="./post.php?new_id=<?=$new['id']?>" class="post-link">    
        <img src="./photos/<?php echo $new['src_name'] ?>">
        <?php
                    echo('
                            <div class="post-info">
                                <div class="post-meta">
                                    <div name="title" class="post-date">'.$new['title'].'</div>
                                </div>
                                <h3 name="post-title" class="post-title">'.$new['intro_text'].'</h3>
                            </div>
                    </a>
                </div>
            </div>
            ');
                    }
        ?>
    </div>

<!-- about me -->

    <div id="about" class="about_me">
        <div class="text_about">
            Серьёзно хочешь тут вычитать что-то интересное?
            Да сказать и не нечего...
            Данный шаблон демонстрирет элементарный и понятный для чтения проект со странными событиями.
            <br>
            P.S. Смотри последнюю новость. 
        </div>

        <div class="ph">
            <img class="photo_about" src="./photos/about_me.jpg">
        </div>
    </div>



<!-- email -->
    <div id="form">
        <form class="form" action="send.php" method="post">
            <div class="pageTitle title"> Для всязи с нами </div>
            <div class="secondaryTitle title">Пожалуйста, заполните форму.</div>
            <input type="text" name = "name" class="name formEntry" placeholder="Имя" />
            <input type="text" name="email" class="email formEntry" placeholder="Email"/>
            <textarea name="message" class="message formEntry" placeholder="Сообщение"></textarea>
                <br>
            <button class="submit formEntry" type="submit">Отправить</button>
          </form>
    </div>


<!-- comments -->
    <form name="comment" action="comment.php" method="post">
        <div class="form-at">
            <div class="validate-input-at w-50" data-validate="Обязательное поле">
                <input class="input-at" type="text" name="name" placeholder="Ваше имя" />
                <span class="focus-input-at"></span>
            </div>
            <div class="validate-input-at" data-validate="Обязательное поле">
                <textarea class="input-at" name="text_comment" placeholder="Ваше сообщение"></textarea>
                <span class="focus-input-at"></span>
            </div>
            <input type="hidden" name="page_id" value="150" />
            <button class="form-at-btn">Отправить</button>
        </div>
    </form>
    <div class="result">
        <?php
    $page_id = 150;// Уникальный идентификатор страницы (статьи или поста)
    $mysqli = new mysqli("localhost", "root", "root", "news_project");
    $result_set = $mysqli->query("SELECT * FROM `comments` WHERE `page_id`='$page_id'"); 
    while ($comment = mysqli_fetch_array($result_set)) {
        echo($comment['name']);
        echo ": "; 
        echo($comment['text_comment']);
        echo "<br/>";
    }
        ?>
    </div>

<!-- footer -->
    <footer id="footer_main">
        <section class="footer">
            <div class="social">
                <a href="https://www.instagram.com/halwa_hm/"><i class="fab fa-instagram"></i></a>
                <a href="https://vk.com/id318776403"><i class="fab fa-vk"></i></a>
                <a href="http://tiktok.com/@daprostohalwa"><i class="fab fa-tiktok"></i></a>
            </div>
            <p class="copyright">
                @Halwa_hm 2022
            </p>    
        </section>
    </footer>
    
</body>
</html>