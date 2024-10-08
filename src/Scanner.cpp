#include "Scanner.hpp"
#include "error.hpp"
#include <iostream>

Scanner::Scanner(std::string source): source(source) {}

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()){
        start = current;
        scanToken();
    }
    tokens.emplace_back(Token(TokenType::EOFF, "",line));
    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;

        //double characters
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL: EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL: LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL: GREATER);
            break;
        
        case '/':
            if (match('/')){
                //comment
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(SLASH);
            }
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        //handlnne strings
        case '"': string(); break;

        default:
            if(isDigit(c)){
                number();
            }  else if(isAlpha(c)) {
                identifier();
            }
            else {
                error(line, "Unexpected character.");
            }

            break;
    }
}

bool Scanner::isAtEnd() {
    return current >= source.size();
}

char Scanner::advance() {
    return source[current++];
}

char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if(current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

void Scanner::addToken(TokenType type) {
  std::string text = source.substr(start, current - start);
  tokens.emplace_back(Token(type, text, line));
}

void Scanner::addToken(TokenType type, std::any literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;

    if(source[current+1] != expected) return false;

    current++;
    return true;
}

void Scanner::string(){
    while(peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) {
        error(line, "Unterminated string.");
    }

    //closting ".
    advance();

    std::string value { source.substr(start + 1, current - 1 - start + 1) };
    addToken(STRING, value);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || 
    (c >= 'A' && c <= 'Z')||
    c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void Scanner::number() {
    char c = peek();
    while (isDigit(peek())) advance();
    c = peek();
    c = peekNext();
    //look for a fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        advance();

        while(isDigit(peek())) advance();
    }
    double number = std::stod(source.substr(start, current - start));
    addToken(NUMBER, number);
}

void Scanner::identifier() {
    while(isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current - start);
    TokenType type;
    if(keywords.find(text) != keywords.end()) {
        type = keywords[text];
    } else {
        type = IDENTIFIER;
    }

    addToken(type);
}
