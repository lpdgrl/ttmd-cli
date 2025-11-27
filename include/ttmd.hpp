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
#include <array>
#include <vector>
#include <unordered_set>

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
    TTMD(const TTMD& other) = delete;
    TTMD(TTMD&& other) = delete;

    TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");

    void Parse();
    void WriteTODOFile() const;
    void SetKeyWordParsed(std::string_view) noexcept;
    

private:
    std::uint32_t CalcCRCFile(const char* buffer, size_t length, std::uint32_t);
    std::uint32_t CalcCRC32(const char* buffer, size_t length, std::uint32_t crc_value = 0xFFFFFFFF);
    std::uint32_t ReflectValue32Bit(std::uint32_t value, int bits) const;
    void InitCRC32();

    std::string keyword_;
    std::filesystem::path path_to_repo_;
    std::filesystem::path path_to_hpp_;
    std::filesystem::path path_to_cpp_;
    std::deque<std::filesystem::directory_entry> query_files_;
    std::unordered_map<std::string, std::string> todo_files_;


    std::array<std::uint32_t, 256> crc_table_;
};

struct CSVRecordFile {
    std::string file_name;
    std::string path_to_file;
    std::uint32_t crc_line = 0;
    int number_line = 0;
};

struct CSVFile {
    std::string file_name;
    std::string path_to_file;
    std::uint32_t crc_file = 0;
};

class CSV {
public:
    CSV() = delete;
    static void GenerateCSVFile(const std::vector<CSVFile>& csv_files);
    static void GenerateCSVRecord();
    static bool WriteToFile(std::string_view path_to_file, const char* buffer, size_t length);
    static bool ReadFile(std::string_view path_to_file);
};
