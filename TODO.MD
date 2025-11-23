## TODO

* [x] 1. Парсинг файла и поиск комментария начинающего с заданного ключевого слова.

* [x] 2. Добавление найденных TODO-комментариев в TODO-файл репозитория, где был поиск

* [x] 3. В файл TODO.MD дописывается checkbox с задачей, датой, строкой, и название файла

* [x] 4. Если файл TODO.MD отсутствует в корне репозитория, то создается новый.

* [ ] 5. Добавить проверку, что если файл не найден, то создан новый файл. Возвращать bool результата выполнения.

* [ ] 7. Протестировать на Windows и MacOS.

* [x] 8. Путь к директориям (которые нужно парсить) репозитория указываются аргументами при запуске программы.

* [ ] 9. Придумать как отслеживать изменения и существующие задачи в TODO.MD чтобы не было дубликатов.

* [ ] 10. Отслеживание нумерации у существующих задач в TODO.MD

* [ ] 11. Хранение истории чтения файлов и TODO в history.csv 

* [ ] 12. Расчёт хэша на основе изменения для каждого прочитанного файла (CRC32)

* [ ] 13. Чтение файла с историей перед добавлением в TODO.MD

* [ ] 14. Запись истории в history.csv

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:90>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:79>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:68>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:60>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:30>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:42>. Adding date: 2025-11-23 19:53

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-23 19:53
