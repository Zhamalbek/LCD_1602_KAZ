Сәлеметсіз ба! arduino UNO патформасына қазақша әріптерді енгізу мүмкіндігін жасадық. Төмендегі орысша әріптеріне қазақ әріптерін қостық
https://github.com/ssilver2007/LCD_1602_RUS
<iframe width="560" height="315" src="https://www.youtube.com/embed/zqnYTexQu8I" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
# LCD_1602_KAZ
Arduino LCD 16x02 display with I2C interface RUSSIAN with NO CYRILLIC symbols set

Библиотека позволяет использовать русские символы при использовании LCD дисплеев, подключенных по интерфейсу I2C, без встроенной кириллицы.
Максимально возможно отображение 8 уникальных по начертанию русских символа (например Ж, Д, И, Ю и т.п.)
Символы, одинаковые по начертанию с английскими (A, B, C, O, P и т.п.) используются из английского набора символов.
Дополнительно встроена возможность печати знака градуса Цельсия. Для этого в тексте программы необходимо набрать
код UTF-8 (Alt+0176)

Должна быть установелна базовая библиотека LiquidCrystal_I2C.
Для Arduino, например, может быть рекомендована эта: https://github.com/marcoschwartz/LiquidCrystal_I2C

Файлы примеров:

HelloWorld - простой пример вывода кириллических символов на LCD экран

HelloWorldCustom - пример вывода задаваемых пользователем и кириллических символов на LCD  экран

SerialToLCD - Ввод символов (в т.ч. кириллических) с монитора порта и их вывод на LCD экран

(c) Сергей Сироткин

По вопросам обращаться:
Zhamalbek.kz@mail.ru
