#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <list>
#include "Token.hpp"

class Scanner {
private:
    int start = 0;
    int current = 0;
    int line = 1;

    void scanToken();    

    bool isAtEnd();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::any literal);


public:
    const std::string source;
    std::list<Token> tokens;

    Scanner(std::string source);

    std::list<Token> scanTokens();
};

#endif