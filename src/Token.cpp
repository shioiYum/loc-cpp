#include "Literal.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include <string>
#include <any>

Token::Token(TokenType type, 
            std::string lexeme, 
            LiteralData literal, 
            int line): type(type), lexeme(lexeme), literal(literal), line(line)
 {}


std::ostream& operator<<(std::ostream& out, const Token& token) {
    std::string type_string;
    switch (token.type) {
        case LEFT_PAREN: type_string = "LEFT_PAREN"; break;
        case RIGHT_PAREN: type_string = "RIGHT_PAREN"; break;
        case LEFT_BRACE: type_string = "LEFT_BRACE"; break;
        case RIGHT_BRACE: type_string = "RIGHT_BRACE"; break;
        case COMMA: type_string = "COMMA"; break;
        case DOT: type_string = "DOT"; break;
        case MINUS: type_string = "MINUS"; break;
        case PLUS: type_string = "PLUS"; break;
        case SEMICOLON: type_string = "SEMICOLON"; break;
        case SLASH: type_string = "SLASH"; break;
        case STAR: type_string = "STAR"; break;
        case BANG: type_string = "BANG"; break;
        case BANG_EQUAL: type_string = "BANG_EQUAL"; break;
        case EQUAL: type_string = "EQUAL"; break;
        case EQUAL_EQUAL: type_string = "EQUAL_EQUAL"; break;
        case GREATER: type_string = "GREATER"; break;
        case GREATER_EQUAL: type_string = "GREATER_EQUAL"; break;
        case LESS: type_string = "LESS"; break;
        case LESS_EQUAL: type_string = "LESS_EQUAL"; break;
        case IDENTIFIER: type_string = "IDENTIFIER"; break;
        case STRING: type_string = "STRING"; break;
        case NUMBER: type_string = "NUMBER"; break;
        case AND: type_string = "AND"; break;
        case CLASS: type_string = "CLASS"; break;
        case ELSE: type_string = "ELSE"; break;
        case FALSE: type_string = "FALSE"; break;
        case FUN: type_string = "FUN"; break;
        case FOR: type_string = "FOR"; break;
        case IF: type_string = "IF"; break;
        case NIL: type_string = "NIL"; break;
        case OR: type_string = "OR"; break;
        case PRINT: type_string = "PRINT"; break;
        case RETURN: type_string = "RETURN"; break;
        case SUPER: type_string = "SUPER"; break;
        case THIS: type_string = "THIS"; break;
        case TRUE: type_string = "TRUE"; break;
        case VAR: type_string = "VAR"; break;
        case WHILE: type_string = "WHILE"; break;
        case EOFF: type_string = "EOF"; break;
        default: type_string = "UNKNOWN"; break;
    }

    std::string result = "TYPE: " + type_string + "\nlexeme: " + token.lexeme + "\n-------\n";
    out << result;
    return out;
}

