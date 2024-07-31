#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "error.hpp"
#include "Scanner.hpp"

bool hadError = false;

void run(std::string source) {
    Scanner scanner = Scanner(source);
    
    std::list<Token> tokens = scanner.scanTokens();

    //do processing
    for(Token token: tokens) {
        std::cout << token << '\n';
    }

}

//error handeling code

void report(int line, std::string where, std::string message) {
    std::cerr << "[line "  << line << "] Error" << where << ": " << message;
    hadError = true;    
}

void error(int line, std::string message) {
    report(line, "", message);
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

    if (hadError) exit(EXIT_FAILURE);
}

void runPrompt() {
    std::string inputBuf{};
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, inputBuf);
        run(inputBuf);
        hadError = false;
    }
}

/*int main(int argc, char * argv[]) {
    if(argc > 2)     {
        std::cout << "Usage: cpplox [script]\n";
        exit(EXIT_FAILURE);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
}*/          

