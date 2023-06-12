// Подключаем библиотеку для работы с жидкокристаллическим
// экраном (англ. Liquid Crystal Display или просто LCD)
#include <LiquidCrystal.h>
// Объявляем объект, для управления дисплеем. Для его создания
// необходимо указать номера пинов, к которым он подключен в
// порядке: RS E DB5 DB6 DB7 DB8
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void setup()
{
 // начинаем работу с экраном. Сообщаем объекту количество
 // строк и столбцов. Опять же, вызывать pinMode не требуется:
 // функция begin сделает всё за нас
 lcd.begin(16, 2);
 // печатаем сообщение на первой строке
 // lcd.print("Zhmyshenko Valeriy Albertovich");
  lcd.print("KATA BAPBAP");
}
void loop()
{
 // скроллим строку раз в 150мс
  lcd.scrollDisplayLeft();
  delay(150);
}