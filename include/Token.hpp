#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.hpp"
#include <any>
#include <string>

class Token {
private:    
    const TokenType type;
    const std::string lexeme;
    const std::any literal;
    const int line;

public:
    //constumers
    Token(TokenType type, std::string lexeme, std::any literal, int line);
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

#endif