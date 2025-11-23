#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <deque>
#include <unordered_map>
#include <chrono>
#include <ctime>

using ResultParseCMD = std::unordered_map<std::string, std::string>;

const std::string usage_cmd(R"(Usage ttmd: 
\n-d: <absolute path to repository> 
\n-hpp: <name of the directory when are storing .hpp or .h files>
\n-cpp: <name of the directory when are storing .cpp files
\n-k: <keyword> for is parsing. Default value is // TODO:
\n-h: help.)");

ResultParseCMD ParseComandLine(int argc, char** argv);

class TTMD {
public:
    TTMD() = delete;
    TTMD(const TTMD& other) = delete;
    TTMD(TTMD&& other) = delete;

    TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");

    void Parse();
    void WriteTODOFile() const;
    void SetKeyWordParsed(std::string_view);

private:
    std::string keyword_;
    std::filesystem::path path_to_repo_;
    std::filesystem::path path_to_hpp_;
    std::filesystem::path path_to_cpp_;
    std::deque<std::filesystem::directory_entry> query_files_;
    std::unordered_map<std::string, std::string> todo_files_;
};
