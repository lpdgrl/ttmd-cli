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
#include <print>
#include <format>

using ResultParseCMD = std::unordered_map<std::string, std::string>;

const std::string usage_cmd(R"(Usage ttmd: 
\n -d: <absolute path to repository> 
\n -hpp: <name of the directory when are storing .hpp or .h files>
\n -cpp: <name of the directory when are storing .cpp files
\n -k: <keyword> for is parsing. Default value is // TODO:
\n -h: help.)");

ResultParseCMD ParseComandLine(int argc, char** argv);

namespace fs = std::filesystem;

constexpr size_t kBufferSize = 4096;

// Structure in CSVRecordFile:
//      first column;   two_column;         three column;   four column;   fifth column;
//      <file_name>;    <path_to_file>;     <TODO>          <crc_line>;     <line_number>;
struct CSVRecordFile {
    std::string file_name;
    std::string path_to_file;
    std::string todo;
    std::uint32_t crc_line = 0;
    int line_number = 0;
};

std::string ToString(const CSVRecordFile& csv_record_file);
std::ostream& operator<<(std::ostream& out, const CSVRecordFile& csv_record_file);

// Structure in CSVfile:
//      first column;   two column;         three column;   four column;
//      <file_name>;    <path_to_file>;     <crc_file>;     <line_number>
struct CSVFile {
    std::string file_name;
    std::string path_to_file;
    std::uint32_t crc_file = 0;
    unsigned int line_number = 0;
};

std::string ToString(const CSVFile& csv_file);
std::ostream& operator<<(std::ostream& out, const CSVFile& csv_file);

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
    bool Exists(const std::vector<fs::path>& paths, std::string_view str_out) const;

    void ReadHistoryFile();
    void ReadCacheLinesFiles();

    std::uint32_t ReadFileAndCalcCrc(const fs::path& path) const;
    void UpdateCacheInCsvFile() const;
    void UpdateCacheInCsvRecordFiles();

    bool CheckHashFile(std::string_view filename, std::uint32_t crc_file) const;
    
    std::uint32_t CalcCRCFile(const char* buffer, size_t length, std::uint32_t) const;
    std::uint32_t CalcCRC32(const char* buffer, size_t length, std::uint32_t crc_value = 0xFFFFFFFF) const;
    std::uint32_t ReflectValue32Bit(std::uint32_t value, int bits) const;
    void InitCRC32();

    std::string keyword_;
    
    fs::path path_to_repo_;
    fs::path path_to_hpp_;
    fs::path path_to_cpp_;

    unsigned int line_number = 0;

    std::deque<fs::directory_entry> query_files_;
    std::unordered_map<std::string, std::string> todo_files_;

    std::array<std::uint32_t, 256> crc_table_;

    using DeqIterCsvFile = std::deque<CSVFile>::iterator;
    std::deque<CSVFile> cache_csv_file_;
    std::unordered_map<std::string, DeqIterCsvFile> cache_csv_file_iter_;

    std::unordered_map<std::uint32_t, CSVRecordFile> cache_csv_lines_;
};

class CSV {
public:
    CSV() = delete;

    CSV(const CSV& csv) = delete;
    CSV& operator=(const CSV& csv) = delete;

    CSV(CSV&& csv) = delete;
    CSV&& operator=(CSV&& csv) = delete;
    
    ~CSV() = delete;

    static void GenerateCSVFile(const std::vector<CSVFile>& csv_files);
    static void GenerateCSVRecord(const std::vector<CSVRecordFile>& csv_record_files);
    static bool WriteToFile(std::string_view path_to_file, const char* buffer, size_t length);
    static std::optional<CSVFile> ReadFile(std::string_view path_to_file);
    static std::optional<CSVFile> ReadFromString(std::string_view csv_from_string);
    static std::optional<CSVRecordFile> ReadRecFileFromString(std::string_view csv_from_string);
};