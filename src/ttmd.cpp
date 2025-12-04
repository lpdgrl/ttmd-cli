#include "../include/ttmd.hpp"

TTMD::TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword)
        : keyword_(keyword)
        , path_to_repo_(path_repo)
        , path_to_hpp_(path_to_repo_.string() + name_dir_hpp.data())
        , path_to_cpp_(path_to_repo_.string() + name_dir_cpp.data()) {
            InitCRC32();
}

void TTMD::ReadHistoryFile() {
    fs::path history_file = path_to_repo_ / ".history" / "history.csv";
     
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
            cache_csv_file_.push_back(csv_file);
            cache_csv_file_iter_[csv_file.file_name] = std::prev(cache_csv_file_.end());
        }
    }
}

void TTMD::ReadCacheLinesFiles() {
    fs::path cache_lines = path_to_repo_ / ".history" / "cache_lines";

    if (!fs::exists(cache_lines) || !fs::is_directory(cache_lines))  {
        std::cerr << "Directory doesn't exist: " << cache_lines << std::endl;
        return;
    }

    bool found_any_file = false;

    for (const auto& entry : fs::recursive_directory_iterator(cache_lines)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        found_any_file = true;

        std::ifstream ifs(entry.path(), std::ios::in);
        if (!ifs) {
            std::println("Not opened this file: <{}>", entry.path().filename().string());
            continue;
        }

        std::string line_sep_dot_comma;
        while (std::getline(ifs, line_sep_dot_comma)) {
            if (auto opt_csv_file_lines = CSV::ReadRecFileFromString(line_sep_dot_comma); opt_csv_file_lines.has_value()) {
                CSVRecordFile csv_record_file = opt_csv_file_lines.value();
                std::cout << csv_record_file;
                cache_csv_lines_[csv_record_file.crc_line] = csv_record_file;
            }
        }
    }

    if (!found_any_file) {
        std::cerr << "No regular files found in directory: " << cache_lines << std::endl;
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
            std::println("{} {} exists.", str_out, path.string());
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
    fs::path todo_history = path_to_repo_ / ".history";
    fs::path history_line_file_cache = path_to_repo_ / ".history" / "cache_lines";
    // Files
    fs::path todo_filename = path_to_repo_ / "TODO.MD";
    fs::path history_file = todo_history / "history.csv";

    std::vector<fs::path> paths_dirs{todo_history, history_line_file_cache};    
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

std::uint32_t TTMD::ReadFileAndCalcCrc(const fs::path& path) const {
    char buffer[kBufferSize]; 
    std::ifstream ifs(path, std::ios::binary);
    std::uint32_t crc_file = 0;

    // TODO: Add std::vector<std::uint8_t>
    do {
        ifs.read(buffer, kBufferSize);
        crc_file = CalcCRCFile(buffer, ifs.gcount(), crc_file);
    } while (ifs);

    crc_file ^= 0xFFFFFFFF;

    return crc_file;
}

void TTMD::UpdateCacheInCsvFile() const {
   std::vector<CSVFile> csv_files;

    for (const auto& csv_file : cache_csv_file_) {
        csv_files.push_back(CSVFile{
            .file_name = csv_file.file_name,
            .path_to_file = csv_file.path_to_file,
            .crc_file = csv_file.crc_file,
            .line_number = csv_file.line_number
        });
    }

    CSV::GenerateCSVFile(csv_files);
}

// TODO: What is to doing?
void TTMD::UpdateCacheInCsvRecordFiles(const std::vector<CSVRecordFile>& csv_record_files) const {
    if (csv_record_files.empty()) {
        return;
    }

    CSV::GenerateCSVRecord(csv_record_files);
}

bool TTMD::CheckHashFile(std::string_view filename, std::uint32_t crc_file) const {
    const auto csv_file = cache_csv_file_iter_.at(filename.data());
    std::cout << std::hex << "csv_file " << filename << " from cache: " << csv_file->crc_file << " crc_calc: " << crc_file << std::endl;
    
    return csv_file->crc_file == crc_file;
}

bool TTMD::IsCheckHashLine(std::uint32_t crc_line) const {
    auto it_crc_line = cache_csv_lines_.find(crc_line); 
    return it_crc_line != cache_csv_lines_.end();
}

void TTMD::EnQueueDirectoryEntry() {
    for (const auto& entry :  std::filesystem::recursive_directory_iterator(path_to_hpp_)) {
        if (entry.is_regular_file()) {
            queue_pending_files_.push_back(entry);
        }
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path_to_cpp_)) {
        if (entry.is_regular_file()) {
            queue_pending_files_.push_back(entry);
        }
    }
}

void TTMD::Parse() {
    // Read history.csv
    ReadHistoryFile();
    // Read all csv files in directory .history/cache_lines
    ReadCacheLinesFiles();

    // Add files to queue for pending from include and src
    EnQueueDirectoryEntry();

    if (queue_pending_files_.empty()) {
        std::cerr << "Query of files is empty!" << std::endl;
        return;
    }

    std::unordered_set<std::string> files_with_todo;
    std::vector<CSVFile> csv_files;
    std::vector<CSVRecordFile> csv_file_lines;

    bool cache_invalid = false;
    unsigned int line_number_csv_file = cache_csv_file_.size() == 0 ? 0 : cache_csv_file_.size();

    // TODO: Take it out into methods
    while (!queue_pending_files_.empty()) {
        auto& entry = queue_pending_files_.front();
        std::string file_name(entry.path().filename());
        std::uint32_t crc_file = ReadFileAndCalcCrc(entry.path());

        auto it_find_file = cache_csv_file_iter_.find(file_name); 
        
        if (it_find_file == cache_csv_file_iter_.end()) {

            CSVFile csv_file{
              .file_name = file_name,
              .path_to_file = entry.path().string(),
              .crc_file = crc_file,
              .line_number = cache_csv_file_.size() == 0 ? line_number_csv_file++ : static_cast<unsigned int>(cache_csv_file_.size())
            };

            std::string path_to_write(path_to_repo_.string() + ".history/history.csv");
            std::string str_from_csv_file(ToString(csv_file));

            CSV::WriteToFile(path_to_write, str_from_csv_file.data(), str_from_csv_file.size());
        }

        if (it_find_file != cache_csv_file_iter_.end()) {
            if (CheckHashFile(file_name, crc_file)) {
                queue_pending_files_.pop_front();
                continue;
            }
            cache_invalid = true;

            it_find_file->second->crc_file = crc_file;
        }
        
        std::string path_to_file(entry.path().string());
        std::ifstream ifs(path_to_file.data(), std::ios::in);

        if (!ifs) {
            std::cerr << "Error to open file <" << file_name << ">" << std::endl;
            queue_pending_files_.pop_front();
            continue;
        }

        // TODO: Think about optimization
        std::cout << "Begining to read file <" << file_name << ">" << std::endl;

        std::string read_line;
        int number_row = 0;

        std::uint32_t crc_line_prev = 0;
        bool is_adding_todo = false;

        while (std::getline(ifs, read_line)) {
            ++number_row;
            std::uint32_t crc_read_line = CalcCRC32(read_line.data(), read_line.size());
        
            if (is_adding_todo) {
                auto& ref_csv_file_lines = csv_file_lines.back();
                ref_csv_file_lines.crc_line = ref_csv_file_lines.crc_line ^ crc_read_line;
                is_adding_todo = false;

                if (!IsCheckHashLine(ref_csv_file_lines.crc_line)) {
                    std::string key(ref_csv_file_lines.file_name + ':' + std::to_string(ref_csv_file_lines.line_number));
                    todo_files_.emplace(key, ref_csv_file_lines.todo);
                } else {
                    csv_file_lines.pop_back();
                }
            }

            if (read_line.contains("// " + keyword_)) {
                std::string normalize_line(Normalize(read_line));

                std::println("TODO from file <{}> on row <{}> CRC line: <{}> Normalize line <{}>", file_name, number_row, (crc_line_prev ^ crc_read_line), normalize_line);

                csv_file_lines.push_back(CSVRecordFile{
                    .file_name = file_name,
                    .path_to_file = path_to_file,
                    .todo = normalize_line,
                    .crc_line = crc_line_prev ^ crc_read_line,
                    .line_number = number_row
                });

                is_adding_todo = true;
            } 
            crc_line_prev = crc_read_line;
        } 
        queue_pending_files_.pop_front();
    }

    if (cache_invalid) {
        UpdateCacheInCsvFile();
    }

    if (cache_csv_lines_.empty()) {
        CSV::GenerateCSVRecord(csv_file_lines);
    } else {
        UpdateCacheInCsvRecordFiles(csv_file_lines);
    }

    WriteTODOFile();
}

// TODO: Add unit test for WriteTODOFile
void TTMD::WriteTODOFile() const {
    namespace krn = std::chrono;

    if (todo_files_.empty()) {
        std::println("Not todo for writing to file.");
        return;
    }

    // TODO: Add the current date and time to the method
    auto now = krn::system_clock::now();
    std::time_t t = krn::system_clock::to_time_t(now);

    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M");

    std::string date_time(oss.str());

    fs::path path_to_todo = path_to_repo_ / "TODO.MD";
    std::ofstream ofs(path_to_todo, std::ios::app);

    std::string checkbox = R"(* [ ] )";
    for (const auto& [key, value] : todo_files_) {
        ofs << '\n';
        ofs << checkbox << value.todo.substr(value.todo.find_first_not_of('/'), value.todo.size()) << ". From file: <" << key << ">. Adding date: " << date_time;
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

std::uint32_t TTMD::CalcCRCFile(const char* buffer, size_t length, std::uint32_t crc_value) const {
    return CalcCRC32(buffer, length, crc_value);
}

void TTMD::InitCRC32() {
    // defined by IEEE 802.3
    static const std::uint32_t poly = 0x04C11DB7;

    for (size_t i = 0; i < crc_table_.size(); ++i) {
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
std::uint32_t TTMD::CalcCRC32(const char* buffer, size_t length, std::uint32_t crc_value) const {
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
    
    // TODO: Rewrite. Now is opening for clear file. Remove hardcode
    std::ofstream ofs("/home/lpdgrl/Project/code/ttmd-cli/.history/history.csv"s, std::ios::trunc);
    ofs.close();

    for (const auto& file : csv_files) {
        std::ostringstream oss;

        oss << std::hex << file.crc_file;
        
        std::string crc(oss.str());
        std::string line_to_write(file.file_name + ';' + file.path_to_file + ';' + crc + ';' + std::to_string(file.line_number) + ';');

        // TODO: Remove hardcode for path
        WriteToFile("/home/lpdgrl/Project/code/ttmd-cli/.history/history.csv"s, line_to_write.data(), line_to_write.size());
    }
}

void CSV::GenerateCSVRecord(const std::vector<CSVRecordFile>& csv_record_files) {
    using namespace std::literals;

    if (csv_record_files.empty()) {
        return;
    }

    for (const auto& file : csv_record_files) {
        size_t idx_comma = file.file_name.find_first_of('.');
        std::string filename(file.file_name);
        filename[idx_comma]= '_';
        // TODO: Rewrite. Now is opening for clear file. Remove hardcode
        std::string path("/home/lpdgrl/Project/code/ttmd-cli/.history/cache_lines/" + filename + ".csv");
        // std::ofstream ofs(path, std::ios::trunc);
        // ofs.close();

        std::string line_to_write(ToString(file));

        // TODO: Remove hardcode for path
        WriteToFile(path, line_to_write.data(), line_to_write.size());
    }
}

bool CSV::WriteToFile(std::string_view path_to_file, const char* buffer, [[maybe_unused]] size_t length) {
    std::ofstream ofs(path_to_file.data(), std::ios::app);
    
    if (!ofs) {
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
    size_t idx_three = csv_from_string.find_first_of(';', idx_two + 1);

    result.file_name = csv_from_string.substr(0, idx_first);
    // std::cout << "Test substr filename: " << result.file_name << std::endl;

    result.path_to_file = csv_from_string.substr(idx_first + 1, idx_two - (idx_first + 1));
    // std::cout << "Test substr path to file: " << result.path_to_file << std::endl;

    // std::cout << "Test subst crc file: " << csv_from_string.substr(idx_two + 1, csv_from_string.size() - idx_two - 2) << std::endl;

    result.crc_file = std::stoul(csv_from_string.substr(idx_two + 1, csv_from_string.size() - idx_two - 2).data(), nullptr, 16);

    result.line_number = std::stoi(csv_from_string.substr(idx_three + 1, csv_from_string.size() - idx_three - 1).data());

    return {result};
}

std::optional<CSVRecordFile> CSV::ReadRecFileFromString(std::string_view csv_from_string) {
    if (csv_from_string.empty()) {
        return std::nullopt;
    }

    // Structure in CSVRecordFile:
    //      first column;   two_column;         three column;   four column;   fifth column;
    //      <file_name>;    <path_to_file>;     <TODO>;          <crc_line>;     <line_number>;
    CSVRecordFile result;

    size_t idx_filename = csv_from_string.find_first_of(';');
    size_t idx_path_file = csv_from_string.find_first_of(';', idx_filename + 1);
    size_t idx_todo = csv_from_string.find_first_of(';', idx_path_file + 1);
    size_t idx_crc = csv_from_string.find_first_of(';', idx_todo + 1);
    
    result.file_name = csv_from_string.substr(0, idx_filename);

    result.path_to_file = csv_from_string.substr(idx_filename + 1, idx_path_file - (idx_filename + 1));

    result.todo = csv_from_string.substr(idx_path_file + 1, idx_todo - (idx_path_file + 1));
    
    result.crc_line = std::stoul(csv_from_string.substr(idx_todo + 1, csv_from_string.size() - idx_todo - 2).data(), nullptr, 16);
    
    result.line_number = std::stoi(csv_from_string.substr(idx_crc + 1, csv_from_string.size() - idx_crc - 1).data());

    std::println("TEST: filename: <{}> path to file: <{}> todo record: <{}> crc line: <{}> line number <{}>", result.file_name, result.path_to_file, result.todo, result.crc_line, result.line_number);

    return {result};
}
 
std::optional<CSVFile> CSV::ReadFile(std::string_view path_to_file) {
    std::ifstream ifs(path_to_file.data(), std::ios::in);

    if (!ifs) {
        std::cerr << "Not opened this file: <" << path_to_file << ">" << std::endl;
        return std::nullopt;
    }

    return std::nullopt;
}

std::ostream& operator<<(std::ostream& out, const CSVFile& csv_file) {
    return out << "Filename: <" << csv_file.file_name << "> "
            << "Path to file: <" << csv_file.path_to_file << "> "
            << "CRC of the file: <" << csv_file.crc_file << "> " 
            << "Line number: <" << csv_file.line_number << ">" << std::endl;
}

std::string ToString(const CSVFile& csv_file) {
    std::ostringstream oss;

    oss << std::hex << csv_file.crc_file;

    std::string result(csv_file.file_name + ';' 
        + csv_file.path_to_file + ';' 
        + oss.str() + ';' 
        + std::to_string(csv_file.line_number) + ';');

    return result;
}

std::string ToString(const CSVRecordFile& csv_record_file) {
    std::ostringstream oss;

    oss << std::hex << csv_record_file.crc_line;

    std::string result(csv_record_file.file_name + ';' 
        + csv_record_file.path_to_file + ';' 
        + csv_record_file.todo + ';' 
        + oss.str() + ';' 
        + std::to_string(csv_record_file.line_number) + ';'
    );

    return result;
}

std::ostream& operator<<(std::ostream& out, const CSVRecordFile& csv_record_file) {
    return out << "Filename: <" << csv_record_file.file_name << "> "
        << "Path to file: <" << csv_record_file.path_to_file << "> "
        << "TODO: <" << csv_record_file.todo << "> "
        << "CRC of the file: <" << csv_record_file.crc_line << "> " 
        << "Line number: <" << csv_record_file.line_number << ">" << std::endl;
}
