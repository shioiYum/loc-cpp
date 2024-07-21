#include "Scanner.hpp"

Scanner::Scanner(std::string source): source(source) {}

std::list<Token> Scanner::scanTokens() {
    while (!isAtEnd()){
        start = current;
        scanToken();
    }    
    tokens.push_back(Token(TokenType::EOFF, "", std::any{}, line));
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
    }
}

bool Scanner::isAtEnd() {
    return current >= source.size();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text = source.substr(start, current);
    tokens.push_back(Token(type, text, literal, line));
}
