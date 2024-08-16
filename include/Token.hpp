#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.hpp"
#include <iostream>
#include <any>
#include <string>

class Token {
public:
    //constumers
  Token(TokenType type, std::string lexeme, std::any literal, int line);
  Token(TokenType type, std::string lexeme, int line);
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

    const TokenType type;
    const std::string lexeme;
  const std::any literal;
    const int line;
};

#endif
