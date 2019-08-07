# IOPS Meter

Данная программа предназначена для расчёта производительности файловых хранилищ данных. В качестве примера была принята методика описанная на сайте http://disorder.ru, а именно в статье http://disorder.ru/archives/1054. 
Программа написана на языке C++ с использованием библиотеки Qt 5.13.0.

# Формат данных

Данные должны быть сохранены в текстовом файле, и содержаться в следующем формате:

| Read IOPS  | Write IOPS |
| ------------- | ------------- |
| 25  | 10  |
| 15  | 5  |
| 17  | 9  |
| ...  | ...  |

Значения разделяются символом проблема. Для сборка статистики в unix системах, в проекте имеется скрипт iomon.sh.  [Пример файла](https://github.com/AsteriaGamer/IOPS-Meter/blob/master/Examples/test.txt "Пример файла") можно найти в папке examples.

# Скриншоты
![Главное окно](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_1.png "Главное окно")

![Пример# 1](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_2.png "Пример# 1")

![Пример# 2](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_3.png "Пример# 2")
