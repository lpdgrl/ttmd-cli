#include "../include/ttmd.hpp"

TTMD::TTMD(std::string_view path_repo, std::string_view name_dir_hpp, std::string_view name_dir_cpp, std::string_view keyword)
        : keyword_(keyword)
        , path_to_repo_(path_repo)
        , path_to_hpp_(path_to_repo_.string() + name_dir_hpp.data())
        , path_to_cpp_(path_to_repo_.string() + name_dir_cpp.data())
        {}

void TTMD::SetKeyWordParsed(std::string_view keyword) {
    keyword_ = keyword;
}

void TTMD::Parse() {
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
                std::cout << "From file <" << file_name << ">" << " on row " << row << " " << read_line.substr(read_line.find_first_not_of(' '), read_line.size()) << std::endl;
                std::string key(file_name + ":" + std::to_string(row));
                todo_files_[key] = read_line.substr(read_line.find_first_not_of(' '), read_line.size());
            }
        } 
        query_files_.pop_front();
    }

    WriteTODOFile();
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

        if (str.find_first_of('-') != std::string::npos) {
            key = std::move(str);
        } else if (!str.empty() && !key.empty()) {
            result[key] = str;
        }
    }
    
    return result;
}