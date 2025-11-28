#include "../include/ttmd.hpp"

TTMD::TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword)
        : keyword_(keyword)
        , path_to_repo_(path_repo)
        , path_to_hpp_(path_to_repo_.string() + name_dir_hpp.data())
        , path_to_cpp_(path_to_repo_.string() + name_dir_cpp.data())
        {
            InitCRC32();
        }

void TTMD::ReadHistoryFile() {
    fs::path history_file (path_to_repo_.string() + "/.history/history.csv");
    
    if (!fs::exists(history_file)) {
        std::cout << "File: " << history_file << " isn't exists." << std::endl;
        return;
    }

    std::ifstream ifs(history_file, std::ios::in);

    if (!ifs.is_open()) {
        std::cerr << "Not opened this file: <" << history_file << ">" << std::endl;
        return;
    }

    std::string line_sep_comma;
    while (std::getline(ifs, line_sep_comma)) {
        auto opt_csv_file = CSV::ReadFromString(line_sep_comma);
        if (opt_csv_file.has_value()) {
            auto csv_file = opt_csv_file.value();
            std::cout << csv_file;
            cache_csv_file_[csv_file.file_name] = csv_file;
        }
    }
}

bool TTMD::ExistsAllDir(const std::vector<fs::path>& paths) const {
    return Exists(paths, "Directory: ");
}

bool TTMD::ExistsAllFiles(const std::vector<fs::path>& paths) const {
    return Exists(paths, "File: ");
}

bool TTMD::Exists(const std::vector<fs::path>& paths, std::string_view str_out) const {
    bool state = false;

    for (const auto& path : paths) {
        if (fs::exists(path)) {
            std::cout << str_out << path.string() << " exists." << std::endl;
            state = true;
        }
        else {
            state = false;
        }
    }
    
    return state;
}
        
void TTMD::Init() const {
    // Directories
    fs::path todo_history(path_to_repo_.string() + ".history");
    fs::path history_file_cash(path_to_repo_.string() + ".history/cash_files");
    fs::path history_line_file_cash(path_to_repo_.string() + ".history/cash_lines");
    // Files
    fs::path todo_filename(path_to_repo_.string() + "TODO.MD");
    fs::path history_file(todo_history.string() + "/history.csv");

    std::vector<fs::path> paths_dirs{todo_history, history_file_cash, history_line_file_cash};    
    std::vector<fs::path> paths_files{todo_filename, history_file};

    bool state_exists_dir = ExistsAllDir(paths_dirs);
    bool state_exists_files = ExistsAllFiles(paths_files);

    if (state_exists_dir && state_exists_files) {
        return;
    }

    try {
        if (!state_exists_dir) {
            for (const auto& path : paths_dirs) {
                fs::create_directory(path);
                std::cout << "Created a directoriy: " << path << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error create a directory: " << e.what() << std::endl;
        return;
    }

    try {
        if (!state_exists_files) {
            for (const auto& path_file : paths_files) {
                std::ofstream ofs(path_file, std::ios::app);
                if (!ofs.is_open()) {
                    std::cerr << "Error create a file: " << path_file.relative_path() << std::endl;
                }
                std::cout << "Created a file: " << path_file.relative_path() << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error created a file: " << e.what() << std::endl;
    }
}

void TTMD::SetKeyWordParsed(std::string_view keyword) noexcept {
    keyword_ = keyword;
}

std::string TTMD::Normalize(const std::string& in_str) const {
    std::string result(in_str.substr(in_str.find_first_not_of(' '), in_str.size()));
    return result;
}

void TTMD::Parse() {

    ReadHistoryFile();

    std::filesystem::recursive_directory_iterator dir_hpp(path_to_hpp_);
    std::filesystem::recursive_directory_iterator dir_cpp(path_to_cpp_);

    for (const auto& entry : dir_hpp) {
        if (entry.is_regular_file()) {
            query_files_.push_back(entry);
        }
    }

    for (const auto& entry : dir_cpp) {
        if (entry.is_regular_file()) {
            query_files_.push_back(entry);
        }
    }

    std::unordered_set<std::string> files_with_todo;
    std::vector<CSVFile> csv_files;
    
    // TODO: Take it out into methods
    for (const auto& entry : query_files_) {
        std::string path_to_file(entry.path().string());
        std::ifstream ifs(path_to_file.data(), std::ios::in);
        std::string file_name(entry.path().filename());

        if (!ifs.is_open()) {
            std::cerr << "Error to open file <" << file_name << ">" << std::endl;
            query_files_.pop_front();
            continue;
        }

        // TODO: Think about optimization
        std::cout << "Begining to read file <" << file_name << ">" << std::endl;
        std::string read_line;
        int row = 0;
        while (std::getline(ifs, read_line)) {
            ++row;
            if (read_line.contains(keyword_)) {
                std::string normalize_line(Normalize(read_line));
                std::cout << "TODO from file <" << file_name << ">" << " on row " << row << " " << normalize_line << std::endl;
                std::string key(file_name + ":" + std::to_string(row));
                todo_files_[key] = normalize_line;

                if (files_with_todo.insert(path_to_file).second) {
                    csv_files.push_back(CSVFile{
                        .file_name = file_name,
                        .path_to_file = path_to_file,
                        .crc_file = 0
                    });
                }
            }
        } 
        query_files_.pop_front();
    }

    std::unordered_map<std::string, std::uint32_t> crc_files;
    if (!files_with_todo.empty()) {
        for (const auto& file_name : files_with_todo) {
            char buffer[1024]; 
            std::ifstream ifs(file_name.data(), std::ios::binary);
            std::uint32_t crc_file = 0;

            while (ifs.read(buffer, 1024)) {
                crc_file = CalcCRCFile(buffer, ifs.gcount(), crc_file);
            }
            crc_file ^= 0xFFFFFFFF;

            std::cout << "CRC32 for file: " << file_name << " " << std::hex << crc_file << std::endl;
            crc_files[file_name] = crc_file;
        }
    }

    for (auto& file : csv_files) {
        if (auto it = crc_files.find(file.path_to_file); it != crc_files.end()) {
            file.crc_file = it->second;
        }
    }
    
    // // Write to CSV file with hash of source/header files repository
    // CSV::GenerateCSVFile(csv_files);

    if (!files_with_todo.empty()) {
        for (const auto& file_name : files_with_todo) {
            std::ifstream ifs(file_name.data(), std::ios::in);
            std::string line;
            int count_line = 0;

            while (std::getline(ifs, line)) {
                std::uint32_t crc_line = 0;
                count_line++;
                crc_line = CalcCRC32(line.data(), line.size(), crc_line);
                crc_line ^= 0xFFFFFFFF;
                std::cout << std::dec << "FileName: " << file_name << " CRC32 for every line: " <<  count_line << " "; 
                std::cout << std::hex << crc_line << std::endl;
            }
        }
    }

    // WriteTODOFile();
}

// TODO: Add unit test for WriteTODOFile
void TTMD::WriteTODOFile() const {
    namespace krn = std::chrono;

    if (todo_files_.empty()) {
        return;
    }

    // TODO: Add the current date and time to the method
    auto now = krn::system_clock::now();
    std::time_t t = krn::system_clock::to_time_t(now);

    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M");

    std::string date_time(oss.str());

    // TODO: Remove hardcode 'TODO.MD'
    std::ofstream ofs(path_to_repo_.string() + "TODO.MD", std::ios::app);
    std::string checkbox = R"(* [ ] )";

    for (const auto& [key, value] : todo_files_) {
        ofs << '\n';
        ofs << checkbox << value.substr(value.find_first_not_of('/'), value.size()) << ". From file: <" << key << ">. Adding date: " << date_time;
        ofs << '\n';
    }
}

// TODO: Add unit test for ParseCommandLine
ResultParseCMD ParseComandLine(int argc, char** argv) {
    ResultParseCMD result;

    std::string key;
    for (int step = 1; step < argc; ++step) {
        std::string str(argv[step]);

        if (key.empty() && str.find_first_of('-') != std::string::npos) {
            key = std::move(str);
        } else if (!str.empty() && !key.empty()) {
            result[key] = str;
            key.clear();
        }
    }

    return result;
}

std::uint32_t TTMD::CalcCRCFile(const char* buffer, size_t length, std::uint32_t crc_value) {
    return CalcCRC32(buffer, length, crc_value);
}

void TTMD::InitCRC32() {
    // defined by IEEE 802.3
    static const std::uint32_t poly = 0x04C11DB7;

    for (int i = 0; i < crc_table_.size(); ++i) {
        std::uint32_t temp = i;
        temp = ReflectValue32Bit(temp, 8); // Reflect 8-bit input byte
        temp <<= 24;  // Align to top 8 bits of 32-bit register

        for (int j = 0; j < 8; ++j) { // Process 8 bits
            if (temp & 0x80000000) {  // If top bit is set
                temp = (temp << 1) ^ poly;
            } else {
                temp <<= 1;
            }
        }

        // Reflect 32-bit result
        temp = ReflectValue32Bit(temp, 32); 
        crc_table_[i] = temp;
    }
}

std::uint32_t TTMD::ReflectValue32Bit(std::uint32_t value, int bits) const {
    std::uint32_t result = 0;
    for (int i = 0; i < bits; ++i) {
        if (value & 1) {
            result |= 1 << (bits - 1 - i);
        }
        value >>= 1;
    }
    return result;
}

// Realization CRC32
std::uint32_t TTMD::CalcCRC32(const char* buffer, size_t length, std::uint32_t crc_value) {
    // init value is reversing for byte of data
    
    for (size_t i = 0; i < length; ++i) {
        std::uint8_t byte = buffer[i];
        
        // Update CRC: (crc << 8) ^ table[(crc >> 24) ^ byte]
        crc_value = (crc_value >> 8) ^ crc_table_[(crc_value ^ byte) & 0xFF];
    }
    return crc_value;
}

void CSV::GenerateCSVFile(const std::vector<CSVFile>& csv_files) {
    using namespace std::literals;

    if (csv_files.empty()) {
        return;
    }
    
    for (const auto& file : csv_files) {
        std::ostringstream oss;

        oss << std::hex << file.crc_file;
        
        std::string crc(oss.str());
        std::string line_to_write(file.file_name + ';' + file.path_to_file + ';' + crc + ';');

        WriteToFile("/home/lpdgrl/Project/code/ttmd-cli/.history/history.csv"s, line_to_write.data(), line_to_write.size());
    }
}

void CSV::GenerateCSVRecord() {

}

bool CSV::WriteToFile(std::string_view path_to_file, const char* buffer, size_t length) {
    std::ofstream ofs(path_to_file.data(), std::ios::app);

    if (!ofs.is_open()) {
        std::cerr << "Not opened this file: <" << path_to_file << ">" << std::endl;
        return false;
    }

    ofs << buffer << '\n'; 

    return true;
}

std::optional<CSVFile> CSV::ReadFromString(std::string_view csv_from_string) {
    if (csv_from_string.empty()) {
        return std::nullopt;
    }

    // std::cout << "Test string: " << csv_from_string << std::endl;
    CSVFile result;

    size_t idx_first = csv_from_string.find_first_of(';');
    size_t idx_two = csv_from_string.find_first_of(';', idx_first + 1);

    result.file_name = csv_from_string.substr(0, idx_first);
    // std::cout << "Test substr filename: " << result.file_name << std::endl;

    result.path_to_file = csv_from_string.substr(idx_first + 1, idx_two - (idx_first + 1));
    // std::cout << "Test substr path to file: " << result.path_to_file << std::endl;

    // std::cout << "Test subst crc file: " << csv_from_string.substr(idx_two + 1, csv_from_string.size() - idx_two - 2) << std::endl;

    result.crc_file = std::stoul(csv_from_string.substr(idx_two + 1, csv_from_string.size() - idx_two - 2).data(), nullptr, 16);

    return {result};
}

std::optional<CSVFile> CSV::ReadFile(std::string_view path_to_file) {
    std::ifstream ifs(path_to_file.data(), std::ios::in);

    if (!ifs.is_open()) {
        std::cerr << "Not opened this file: <" << path_to_file << ">" << std::endl;
        return std::nullopt;
    }

    return std::nullopt;
}

std::ostream& operator<<(std::ostream& out, const CSVFile& csv_file) {
    return out << "Filename: <" << csv_file.file_name << "> "
            << " Path to file: <" << csv_file.path_to_file << "> "
            << "CRC of the file: <" << csv_file.crc_file << ">" << std::endl;
}