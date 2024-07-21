#include "TokenType.hpp"
#include "Token.hpp"
#include <string>
#include <any>

Token::Token(TokenType type, 
            std::string lexeme, 
            std::any literal, 
            int line): type(type), lexeme(lexeme), literal(literal), line(line)
 {}


std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << token.lexeme;
}

