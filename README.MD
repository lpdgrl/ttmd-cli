## TTMD-CLI - TODO from source file to TODO.MD

## Для чего TTMD-CLI

TTMD-CLI парсит исходники (.hpp или .cpp) и выдергивает комментарии начинающиеся с ключевой фразы и заносит в TODO.MD который лежит в корне репозитория. Если файл TODO.MD не создан, то он будет создан. 

Обычно для TODO в исходниках использую нечто подобное -  "// TODO:". 

## Как собрать и запустить

Клонируем репозиторий:
```shell
git clone https://github.com/lpdgrl/
```

Выполняем сборку в корне репозитория:
```shell
mkdir build && cd build
cmake .. -G Ninja
cmake --build . 
```

Описание ключей для запуска (в угловых скобочках пример. Их вводить не нужно): 
```shell
-d - указываем полный путь до репозитоия который будем парсить. Пример: -d <$HOME/Project/test_repo/>
-hpp - указываем название директории, где хранятся файлы с расширением .hpp\.h Пример: -hpp <include>
-cpp - указываем название директории, где хранятся файлы с расширением .cpp\.cxx Пример: -cpp <src>
-k - указываем, если нужна альтернативная ключевая фраза для парсинга. Пример: -k <"// TODO ">
```

Пример запуска с ключевой фразой по умолчанию:
```shell
    $HOME/Project/ttmd/build/ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src
```

Пример запуска с альтернативной ключевой фразой:
```shell
    $HOME/Project/ttmd/build/ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src -k "// todo: "
```

##  Сообщить о проблеме
Проект пока в сыром состоянии. Могут быть баги или ошибки. 

Если вы нашли баг или хотите предложить улучшение — пожалуйста, создайте Issue:
https://github.com/lpdgrl/ttmd-cli/issues

## ✉️ Email
По всем вопросам и багам: **leopard.grellii@gmail.com**

[TODO проекта](TODO.MD)