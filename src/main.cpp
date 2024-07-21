#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

void run(std::string source) {
    std::cout <<  source << '\n';
}

void runFile(std::string path) {
    const std::filesystem::path correct_path = std::filesystem::u8path(path);
    std::ifstream inf {path};

    if (!inf) {
        std::cerr << "Could not open the file\n";
        exit(EXIT_FAILURE);
    }
    std::ostringstream buf;
    buf << inf.rdbuf();
    std::string code = buf.str();

    run(code);
}

void runPrompt() {
    std::string inputBuf{};
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, inputBuf);
        run(inputBuf);
    }
}

int main(int argc, char * argv[]) {
    if(argc > 2)     {
        std::cout << "Usage: cpplox [script]\n";
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
}          

