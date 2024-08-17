#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <memory>
#include "Expr.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <exception>

class Parser {
public:
  Parser(std::vector<Token>& tokens);
  ~Parser();
  Expr * parse();
  Expr * expression();
  Expr *  equality();
  Expr * comparision();
  Expr * term();
  Expr * factor();
  Expr * unary();
  Expr * primary();

  //for exception
  class ParseError: std::exception {};
  
private:
  std::vector<Token> tokens;
  int current;

  template<typename... TokenType>
  bool match(const TokenType&... tokentypes);
  
  bool matchToken(const TokenType& token);

  Token peek();
  Token advance();
  bool isAtEnd();
  Token previous();
  Token consume(TokenType type, std::string message);
  ParseError parsererror(Token token, std::string message);

  void synchronize();
  
  
  bool check(TokenType type);
  
};
#endif
