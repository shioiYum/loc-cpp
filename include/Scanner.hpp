#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <list>
#include <unordered_map>
#include "Token.hpp"

class Scanner {
private:
    int start = 0;
    int current = 0;
    int line = 1;

    //keyboard hash
    std::unordered_map<std::string, TokenType> keywords {
        {"and", AND},
        {"class" , CLASS},
        {"else", ELSE},
        {"true", TRUE},
        {"false", FALSE},
        {"for", FOR},
        {"fun", FUN},
        {"if", IF},
        {"nil", NIL},
        {"or", OR},
        {"print", PRINT},
        {"return", RETURN},
        {"super", SUPER},
        {"this", THIS},
        {"var", VAR},
        {"while", WHILE}
    };

    void scanToken();    

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    void string();
    bool isDigit(char);
    bool isAlpha(char);
    bool isAlphaNumeric(char);


  void number();
  void identifier();
  void addToken(TokenType type);
  void addToken(TokenType type, std::any literal);
  bool match(char expected);


public:
    const std::string source;
    std::list<Token> tokens;

    Scanner(std::string source);

    std::list<Token> scanTokens();
};

#endif
