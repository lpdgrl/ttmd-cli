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
#include <optional>

using ResultParseCMD = std::unordered_map<std::string, std::string>;

const std::string usage_cmd(R"(Usage ttmd: 
\n-d: <absolute path to repository> 
\n-hpp: <name of the directory when are storing .hpp or .h files>
\n-cpp: <name of the directory when are storing .cpp files
\n-k: <keyword> for is parsing. Default value is // TODO:
\n-h: help.)");

ResultParseCMD ParseComandLine(int argc, char** argv);

namespace fs = std::filesystem;

struct CSVRecordFile {
    std::string file_name;
    std::string path_to_file;
    std::uint32_t crc_line = 0;
    int number_line = 0;
};

// Structure in CSVfile:
//      first column;   two column;         three column;
//      <file_name>;    <path_to_file>;     <crc_file>;

struct CSVFile {
    std::string file_name;
    std::string path_to_file;
    std::uint32_t crc_file = 0;
};

struct CSVFileHasher {
    size_t operator()(const CSVFile& csv_file) const {
        size_t h1 = std::hash<std::string>{}(csv_file.file_name);
        size_t h2 = std::hash<std::string>{}(csv_file.path_to_file);
        size_t h3 = std::hash<uint32_t>{}(csv_file.crc_file);
        return h1 ^ (h2 << 1) ^ (h3 << 4);
    } 
};


class TTMD {
public:
    TTMD(const TTMD& other) = delete;
    TTMD(TTMD&& other) = delete;

    TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword = "// TODO:");

    void Init() const;
    void Parse();
    void WriteTODOFile() const;
    void SetKeyWordParsed(std::string_view) noexcept;

private:
    std::string Normalize(const std::string& in_str) const;
    bool ExistsAllDir(const std::vector<fs::path>& paths) const;
    bool ExistsAllFiles(const std::vector<fs::path>& paths) const;

    void ReadHistoryFile();
    bool CheckHashFile(const fs::path& path) const;
    
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

    std::unordered_map<std::string, CSVFile, CSVFileHasher> readed_csv_files_;
};

class CSV {
public:
    CSV() = delete;
    static void GenerateCSVFile(const std::vector<CSVFile>& csv_files);
    static void GenerateCSVRecord();
    static bool WriteToFile(std::string_view path_to_file, const char* buffer, size_t length);
    static std::optional<CSVFile> ReadFile(std::string_view path_to_file);
};
