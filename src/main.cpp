#include "../include/ttmd.hpp"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << usage_cmd << std::endl;

        return EXIT_FAILURE;
    }
    // TODO: Parsing args to new function
    else if (argc >= 6) {
        auto result = ParseComandLine(argc, argv);
        
        // TODO: Organize in structure
        std::string path_dir;
        std::string name_dir_hpp;
        std::string name_dir_cpp;
        std::string keyword;

        // TODO: Naive verification at empty string
        if (result.count("-d") == 0) {
            std::cout << "Not are -d argument!" << std::endl;
            return EXIT_FAILURE;
        }

        if (result.count("-hpp") == 0) {
            std::cout << "Not are -hpp argument!" << std::endl;
            return EXIT_FAILURE;
        }

        if (result.count("-cpp") == 0) {
            std::cout << "Not are -cpp argument!" << std::endl;
            return EXIT_FAILURE;
        }
        
        path_dir = result["-d"];
        name_dir_cpp = result["-cpp"];
        name_dir_hpp = result["-hpp"];

        if (result.count("-k") > 1) {
            keyword = result["-k"];
        }

        TTMD ttmd(path_dir, name_dir_hpp, name_dir_cpp);
        ttmd.Init();
        if (!keyword.empty()) { 
            ttmd.SetKeyWordParsed(keyword);
        }
        // TODO: Rename this method of class TTMD
        ttmd.Parse();
    }
    return EXIT_SUCCESS;
}

