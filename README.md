Название файла и пути к нему - константа, потому что для переименования файла нужна не строка, а массив символов, в который строка не хочет преобразовываться нормально и мне было лень делать костыли по типу перевода через цикл или использовать нормальные методы языка. 
Теперь по функционалу:

1: Создаёт файл (если его нет). Если есть, записывает в его конец. Для сохранения внесённых изменений обязательно ввести exit или 0.

2: Выводит всю информацию из файла

3: Выводит строку, находящуюся под введённым номером.
0: Выйти без изменений;
1: Запрашивает ввод, полностью заменяет строку. ID остаётся неизменным.

Суть замены строки заключается в создании второго файла и копирование в него строк из первого файла. Когда программа доходит до нужной строки, запрашивается ввод, который помещается в новый файл, после чего оставшаяся часть файла дозаписывается в новый без изменений. После записи первый файл удаляется, а новый переименовывается в старый. 
