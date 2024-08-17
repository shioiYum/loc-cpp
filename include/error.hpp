#ifndef ERROR_H
#define ERROR_H

#include "Token.hpp"
#include "TokenType.hpp"
#include <string>

void error(int, std::string);
void error(Token token, std::string message);
void report(int, std::string, std::string);

#endif
