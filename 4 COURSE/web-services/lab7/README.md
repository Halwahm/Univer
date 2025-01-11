## P.S. Visual Studio сразу же запускаем от имени администратора, иначе служба не будет регистироваться
### TODO:
1) Создаем проект типа Библиотека службы публикации [ТЫК](https://github.com/DimaXDD/Course4/blob/master/7sem/%D0%9FWS%20(%D0%A1%D0%BC%D0%B5%D0%BB%D0%BE%D0%B2)/Lab7/%D0%A4%D0%BE%D1%82%D0%BE%20%D0%B4%D0%BB%D1%8F%20%D0%B3%D0%B0%D0%B9%D0%B4%D0%B0/1.png)<br/>
2) Копируем мой код (либо делаем по аналогии), подключаем к этому проекту EDM-модель из 6 лабы, как ее делать и подключать [ТЫК](https://github.com/DimaXDD/Course4/tree/master/7sem/%D0%9FWS%20(%D0%A1%D0%BC%D0%B5%D0%BB%D0%BE%D0%B2)/Lab6#readme)<br/>
3) По факту, служба готова, можно тестить<br/>
Для теста службы с браузера заходим на `http://localhost:40124/SyndicationServiceLibrary/Feed1`<br/>
4) Просто заливаем этот проект на IIS и проверяем, что запускается<br/>
5) Для создания хоста нашей службы, создаем консольное приложение и подключаем нашу службу [ТЫК](https://github.com/DimaXDD/Course4/blob/master/7sem/%D0%9FWS%20(%D0%A1%D0%BC%D0%B5%D0%BB%D0%BE%D0%B2)/Lab7/%D0%A4%D0%BE%D1%82%D0%BE%20%D0%B4%D0%BB%D1%8F%20%D0%B3%D0%B0%D0%B9%D0%B4%D0%B0/2.png) и [ТЫК](https://github.com/DimaXDD/Course4/blob/master/7sem/%D0%9FWS%20(%D0%A1%D0%BC%D0%B5%D0%BB%D0%BE%D0%B2)/Lab7/%D0%A4%D0%BE%D1%82%D0%BE%20%D0%B4%D0%BB%D1%8F%20%D0%B3%D0%B0%D0%B9%D0%B4%D0%B0/3.png)<br/>
! Обязательно смотрим на файлы `App.config`, какое там содержимое и порты<br/>
6) Создаем WinForm-приложение и копируем мой код, запускаем host-приложение и форму, после запуска вводим id студента и формат вывода. Должно все работать)<br/>