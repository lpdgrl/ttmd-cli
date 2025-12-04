## TODO

* [x] 1. Парсинг файла и поиск комментария начинающего с заданного ключевого слова.

* [x] 2. Добавление найденных TODO-комментариев в TODO-файл репозитория, где был поиск

* [x] 3. В файл TODO.MD дописывается checkbox с задачей, датой, строкой, и название файла

* [x] 4. Если файл TODO.MD отсутствует в корне репозитория, то создается новый.

* [x] 5. Путь к директориям (которые нужно парсить) репозитория указываются аргументами при запуске программы.

* [x] 6. Придумать как отслеживать изменения и существующие задачи в TODO.MD чтобы не было дубликатов.

* [x] 7. Хранение истории чтения файлов в history.csv 

* [x] 8. Расчёт общего хэша на основе изменения для каждого прочитанного файла (CRC32)

* [x] 9. Расчёт хэша для каждой строки (CRC32)

* [x] 10. Запись общего хэша файла и хэша для каждой строки из файла в csv-файл

* [x] 11. Запись истории в history.csv

* [ ] 12. Добавить проверку, что если файл не найден, то создан новый файл. Возвращать bool как результат выполнения.

* [ ] 13. Протестировать на Windows и MacOS.

* [ ] 14. Отслеживание нумерации у существующих задач в TODO.MD

* [ ] 15. Чтение файла с историей перед добавлением в TODO.MD

* [ ]  TODO: Remove hardcode for path. From file: <ttmd.cpp:462>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:373>. Adding date: 2025-12-04 22:47

* [ ] \n -k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:25>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-12-04 22:47

* [ ]  TODO: What is to doing?. From file: <ttmd.cpp:185>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Rewrite. Now is opening for clear file. Remove hardcode. From file: <ttmd.cpp:450>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:19>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Hello world. From file: <main.cpp:34>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Remove hardcode for path. From file: <ttmd.cpp:485>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Rewrite. Now is opening for clear file. Remove hardcode. From file: <ttmd.cpp:478>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Add std::vector<std::uint8_t>. From file: <ttmd.cpp:159>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Rename this method of class TTMD. From file: <main.cpp:48>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Organize in structure. From file: <main.cpp:13>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:241>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:342>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Maybe class is does not static?. From file: <ttmd.hpp:120>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:283>. Adding date: 2025-12-04 22:47

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:351>. Adding date: 2025-12-04 22:47
