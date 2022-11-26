const months = new Array(13);
months[1]="января";months[2]="февраля"; months[3]="марта";
months[4]="апреля";months[5]="мая"; months[6]="июня";
months[7]="июля"; months[8]="августа"; months[9]="сентября";
months[10]="октября"; months[11]="ноября"; months[12]="декабря";

const time=new Date();
const thismonth=months[time.getMonth()+1];
const date=time.getDate();
let thisyear=time.getYear();
const day=time.getDay() + 1;

if (thisyear < 2000)
  thisyear = thisyear + 1900;
if(day==1) DayofWeek = "Воскресенье";
if(day==2) DayofWeek = "Понедельник";
if(day==3) DayofWeek = "Вторник";
if(day==4) DayofWeek = "Среда";
if(day==5) DayofWeek = "Четверг";
if(day==6) DayofWeek = "Пятница";
if(day==7) DayofWeek = "Суббота";

  setInterval(function() {
    const cd = new Date();
    const clockdat = document.getElementById("clockdat");
    clockdat.innerHTML = cd.toLocaleTimeString();
  }, 1000);