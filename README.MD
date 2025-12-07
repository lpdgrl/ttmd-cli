## TTMD-CLI — Extract TODOs from Source Files into TODO.md

## What is TTMD-CLI?

TTMD-CLI parses source files (.hpp or .cpp) and extracts comments that begin with a specific key phrase, then writes them into a TODO.md file located in the root of the repository.
If TODO.md does not exist, the tool will create it automatically.

Typically, TODO comments look like this: // TODO:.

## How to Build and Run

Clone the repository:
```shell
git clone https://github.com/lpdgrl/ttmd-cli.git
```

Build the project in the repository root:
```shell
mkdir build && cd build
cmake .. -G Ninja
cmake --build . 
```

Command-Line Options
```shell
-d — specify the full path to the repository you want to parse.
Example: -d <$HOME/Project/test_repo/>

-hpp — specify the directory name containing .hpp or .h files.
Example: -hpp <include>

-cpp — specify the directory name containing .cpp or .cxx files.
Example: -cpp <src>

-k — specify an alternative key phrase to search for TODO comments. 
Example: -k <"// TODO ">
```

Example Usage (with default key phrase)
```shell
    $HOME/Project/ttmd/build/ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src
    or 
    ./ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src
```

Example Usage (with custom key phrase)
```shell
    $HOME/Project/ttmd/build/ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src -k "// todo: "
    or
    ./ttmd-cli -d $HOME/Project/ttmd/ -hpp include -cpp src -k "// todo: "
```

##  Reporting Issues

The project is still in an early stage. Bugs and errors may occur.
Windows and macOS support has not been tested.

If you find a bug or want to suggest an improvement, please open an issue:
https://github.com/lpdgrl/ttmd-cli/issues

## ✉️ Contact
For any questions or bug reports: **leopard.grellii@gmail.com**

[**Telegram**](https://t.me/leopardgrelli)

[Project TODO](TODO.MD)