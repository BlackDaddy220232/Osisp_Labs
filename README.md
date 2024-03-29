# Walkdir

Walkdir - это программа на языке C, которая обходит указанную директорию и выводит список файлов и поддиректорий.

# Компиляция

Для компиляции программы `walkdir` вам понадобится компилятор GCC. Убедитесь, что GCC установлен на вашей системе.

1. Склонируйте репозиторий `walkdir`
```
git clone https://github.com/BlackDaddy220232/Osisp_Labs.git
```
3. Перейдите в директорию `Osisp_Labs`:

4. Задите в соответсвующую лабораторную работу

5. Соберите с помощью make
```
make MODE=release
```
## Использование

После успешной компиляции вы можете запустить программу `walkdir` с указанием целевой директории:
```
./walkdir [опции] /путь/к/директории
```
Опции
Программа walkdir поддерживает следующие опции:

-l: Устанавливает опцию символических ссылок.

-d: Устанавливает опцию каталогов.

-f: Устанавливает опцию файлов.

-s: Устанавливает опцию сортировки.
