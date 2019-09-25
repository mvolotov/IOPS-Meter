
# IOPS Meter

Программа предназначена для расчёта производительности файловых хранилищ данных. В качестве примера была принята методика описанная на сайте http://disorder.ru, а именно в статье http://disorder.ru/archives/1054. 
Программа написана на языке C++ с использованием библиотеки Qt 5.13.0.

# Формат данных

Исходные данные должны быть сохранены в текстовом файле, и содержаться в следующем формате:

| Read IOPS  | Write IOPS |
| ------------- | ------------- |
| 25  | 10  |
| 15  | 5  |
| 17  | 9  |
| ...  | ...  |

Левый столбец содержит число операций чтения, правый - число операций записи. В качестве разделителя между столбцами выступает пробел. [Пример файла](https://github.com/AsteriaGamer/IOPS-Meter/blob/master/Examples/test.txt "Пример файла") можно найти в папке examples. 

Для сбора статистики в unix системах, в проекте имеется скрипт iomon.sh. Данный скрипт раз в 5 секунд собирает информацию о нагрузке на хранилище данных и сохраняет эту информацию в текстовый файл, пригодный для обработки программой.

Для сбора статистики в windows системах, можно использовать "монитор производительности", [подробнее об этом.](http://rickardnobel.se/windows-performance-monitor-disk-usage/)

# Диаграмма

На данном рисунке представлена диаграмма, на которой изображены основные классы программы, их методы и атрибуты.

![Диаграмма классов](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_4.png)

# Скриншоты
![Главное окно](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_1.png "Главное окно")

![Пример# 1](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_2.png "Пример# 1")

![Пример# 2](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_3.png "Пример# 2")

![Пример# 3](https://raw.githubusercontent.com/AsteriaGamer/IOPS-Meter/master/Examples/Screenshot_5.png)
