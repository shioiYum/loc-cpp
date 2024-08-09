#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.hpp"
#include "Literal.hpp"
#include <iostream>
#include <any>
#include <string>

class Token {
public:
    //constumers
    Token(TokenType type, std::string lexeme, LiteralData literal, int line);
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

    const TokenType type;
    const std::string lexeme;
    const LiteralData literal;
    const int line;
};

#endif
