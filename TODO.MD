## TODO

* [x] 1. Парсинг файла и поиск комментария начинающего с заданного ключевого слова.

* [x] 2. Добавление найденных TODO-комментариев в TODO-файл репозитория, где был поиск

* [x] 3. В файл TODO.MD дописывается checkbox с задачей, датой, строкой, и название файла

* [x] 4. Если файл TODO.MD отсутствует в корне репозитория, то создается новый.

* [x] 5. Путь к директориям (которые нужно парсить) репозитория указываются аргументами при запуске программы.

* [ ] 6. Добавить проверку, что если файл не найден, то создан новый файл. Возвращать bool результата выполнения.

* [ ] 7. Протестировать на Windows и MacOS.

* [ ] 8. Придумать как отслеживать изменения и существующие задачи в TODO.MD чтобы не было дубликатов.

* [ ] 9. Отслеживание нумерации у существующих задач в TODO.MD

* [ ] 10. Хранение истории чтения файлов и TODO в history.csv 

* [ ] 11. Расчёт общего хэша на основе изменения для каждого прочитанного файла (CRC32)

* [ ] 12. Расчёт хэша для каждой строки (CRC32)

* [ ] 13. Запись общего хэша и для каждой строки хэша в файл (имя файла это файл который читаем)

* [ ] 14. Чтение файла с историей перед добавлением в TODO.MD

* [ ] 15. Запись истории в history.csv

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:17

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:17

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:17

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:131>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:120>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:109>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:101>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:18

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:18

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:18

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:131>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:120>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:109>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:101>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:19

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:19

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:19

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:28

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:28

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:28

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:28

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:28

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:28

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:28

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:28

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:28

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:29

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:29

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:29

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:29

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:29

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:121>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:110>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:102>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:30

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:132>. Adding date: 2025-11-26 22:30

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:30

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:131>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:120>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:109>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:101>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:31

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:31

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:31

* [ ]  TODO: Add unit test for ParseCommandLine. From file: <ttmd.cpp:130>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Remove hardcode 'TODO.MD'. From file: <ttmd.cpp:119>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Add the current date and time to the method. From file: <ttmd.cpp:108>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Naive verification at empty string. From file: <main.cpp:18>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Think about optimization. From file: <ttmd.cpp:46>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Take it out into methods. From file: <ttmd.cpp:34>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Parsing args to new function. From file: <main.cpp:9>. Adding date: 2025-11-26 22:33

* [ ]  TODO: Add unit test for WriteTODOFile. From file: <ttmd.cpp:100>. Adding date: 2025-11-26 22:33

* [ ] TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");. From file: <ttmd.hpp:32>. Adding date: 2025-11-26 22:33

* [ ] \n-k: <keyword> for is parsing. Default value is // TODO:. From file: <ttmd.hpp:22>. Adding date: 2025-11-26 22:33
