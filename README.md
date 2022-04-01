# n-puzzle
15 puzzle

Решение популярной головоломки "Игра в 15", другое название игры "Пятнашки".

Сборка программ осуществляется с помощью с помощью Makefile.

Более подробное описание задания можно найти в файле puzzle.pdf.

Игровое поле в отличие от оригинальной игры может быть большего или меньшего размера. </br>
Задать начальное положение головоломки необходимо как в фалах test1.txt-test6.txt или выбрать ручной ввод значений. </br>
Сгенерировать головоломки нужного образца можно с помощью программы npuzzle-gen.py. </br>
Если головоломка является некорректной или нерешаемой, то программа сообщит об этом. </br>

Для решения был использован алгоритм A* (алгоритм поиска по первому наилучшему совпадению на графе) и различные эвристики. </br>
Так же был дополнительно реализован поиск в ширину, поиск в глубину, модификация жадного поиска, не способного зайти в тупик для этой задачи. </br>
Программы может выводить последовательность действий с пустым блоком (обозначается нулём) и этапы решения головоломки. </br>

Что бы сравнить разные алгоритмы и эвристики запустите программу и следуйте инструкциям.
