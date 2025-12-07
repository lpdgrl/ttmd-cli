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

* [x] 12. Отслеживание нумерации у существующих задач в TODO.MD

* [x] 13. Чтение файла с историей перед добавлением в TODO.MD

* [ ] 14. Что делать, если сделал\удалил TODO?

* [ ] 15. Отсортировать TODO по названию файла и строкам перед записью в TODO.MD 

* [x] 16. Избавиться от hardcode путей в методах в CSV-классе (.history)

* [ ] 17. Добавить запись в .gitignore директории .history

* [ ] 18. Добавить статистику по добавленным TODO и выполненным TODO.

* [ ] 19. Хранение статистики в csv-файле??

* [ ] 20. Rewrite. Now is opening for clear file. Remove hardcode. From file: <ttmd.cpp:515>. Adding date: 2025-12-06 17:04

* [x] 21. Remove hardcode for path. From file: <ttmd.cpp:498>. Adding date: 2025-12-06 17:04

* [ ] 22. Rewrite. Now is opening for clear file. Remove hardcode. From file: <ttmd.cpp:486>. Adding date: 2025-12-06 17:04

* [ ] 23. Wrap in method NormalizeTodo(Remove TODO title). From file: <ttmd.cpp:393>. Adding date: 2025-12-06 17:04

* [ ] 24. Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-12-06 17:04

* [ ] 25. Add unit test for ParseCommandLine. From file: <ttmd.cpp:409>. Adding date: 2025-12-06 17:04

* [ ] 26. Add std::vector<std::uint8_t>. From file: <ttmd.cpp:183>. Adding date: 2025-12-06 17:04

* [ ] 27. Think about optimization. From file: <ttmd.cpp:309>. Adding date: 2025-12-06 17:04

* [ ] 28. Maybe class is does not static?. From file: <ttmd.hpp:127>. Adding date: 2025-12-06 17:04

* [ ] 29. Naive verification at empty string. From file: <main.cpp:19>. Adding date: 2025-12-06 17:04

* [ ] 30.k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:25>. Adding date: 2025-12-06 17:04

* [ ] 31. Add unit test for WriteTODOFile. From file: <ttmd.cpp:368>. Adding date: 2025-12-06 17:04

* [ ] 32. Organize in structure. From file: <main.cpp:13>. Adding date: 2025-12-06 17:04

* [ ] 33. Rename this method of class TTMD. From file: <main.cpp:48>. Adding date: 2025-12-06 17:04

* [ ] 34. Combine verification and create ifstream object and return ref to object of ifstream. . From file: <ttmd.cpp:79>. Adding date: 2025-12-06 17:04

* [ ] 35. What is to doing?. From file: <ttmd.cpp:209>. Adding date: 2025-12-06 17:04

* [x] 36. Remove hardcode for path. From file: <ttmd.cpp:522>. Adding date: 2025-12-06 17:04

* [ ] 37. Take it out into methods. From file: <ttmd.cpp:267>. Adding date: 2025-12-06 17:04

* [ ] 38. Add the current date and time to the method. From file: <ttmd.cpp:377>. Adding date: 2025-12-06 17:04

* [ ] 39. Rewrite. Now is opening for clear file.. From file: <ttmd.cpp:514>. Adding date: 2025-12-07 00:47

* [ ] 40. Rewrite. Now is opening for clear file.. From file: <ttmd.cpp:486>. Adding date: 2025-12-07 00:47

* [ ] 41.<keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:25>. Adding date: 2025-12-07 22:24
