#include "Parser.hpp"
#include "Expr.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include <cstddef>
#include <memory>
#include "error.hpp"
#include <iostream>
#include <stdexcept>

Parser::Parser(std::vector<Token>& tokens): tokens(tokens) {}

Expr * Parser::parse() {
  try {
    return expression();
  } catch(ParseError error) {
    return NULL;
  }
}

Expr *Parser::expression() { return equality(); }


Expr * Parser::equality() {
  Expr * expr = comparision();

  while(match(TokenType::BANG, TokenType::BANG_EQUAL)) {
    Token op = previous();
    Expr * right = comparision();
    expr = new BinaryExpr(std::unique_ptr<Expr>(expr),
				     op,
				     std::unique_ptr<Expr>(right));
    
  }
  return expr;
}

Expr * Parser::comparision() {
  Expr * expr = term();

  while(match(TokenType::GREATER, TokenType::GREATER_EQUAL,
	      TokenType::LESS_EQUAL, TokenType::LESS)) {

    Token op = previous();
    Expr * right = term();
    expr = new BinaryExpr(std::unique_ptr<Expr>(expr),
				     op,
				     std::unique_ptr<Expr>(right));
  }

  return expr;
}

Expr * Parser::unary() {
  while(match(TokenType::BANG, TokenType::MINUS)) {
    Token op = previous();
    Expr * right = unary();
    return new UnaryExpr(op,
			 std::unique_ptr<Expr>(right));
  }

  return primary();
}

Expr * Parser::primary() {
  if(match(TokenType::TRUE)) return new LiteralExpr(true);

  if(match(TokenType::FALSE)) return new LiteralExpr(false);

  if(match(TokenType::NIL)) return new LiteralExpr(NULL);

  if(match(TokenType::NUMBER, TokenType::STRING))
    return new LiteralExpr(previous().literal);

  if(match(TokenType::LEFT_PAREN)) {
    Expr * expr = expression();
    consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
    return new GroupingExpr(std::unique_ptr<Expr>(expr));
  }

  throw parsererror(peek(), "Expect expression. ");
}


Expr * Parser::term() {
  Expr * expr = factor();

  while(match(TokenType::MINUS, TokenType::PLUS)) {
    Token op = previous();
    Expr * right = factor();

    expr = new BinaryExpr(std::unique_ptr<Expr>(expr),
			  op,
			  std::unique_ptr<Expr>(right));
  }

  return expr;
};

Expr * Parser::factor() {
  Expr * expr = unary();

  while(match(TokenType::SLASH, TokenType::STAR)) {
    Token op = previous();
    Expr * right = unary();
    expr = new BinaryExpr(std::unique_ptr<Expr>(expr),
			  op,
			  std::unique_ptr<Expr>(right));
  }
  return expr;
}



template <typename... TokenType>
bool Parser::match(const TokenType&... tokentypes) {
  return (matchToken(tokentypes) || ...);
}


bool Parser::matchToken(const TokenType &tokenType) {
  if(check(tokenType)) {
    advance();
    return true;
  }

  return false;
}

Token Parser::consume(TokenType type, std::string message) {
  if(match(type)) return advance();

  throw parsererror(peek(), message);
}


Parser::ParseError Parser::parsererror(Token token, std::string message) {
  error(token, message);
  return ParseError();
}


bool Parser::check(TokenType type) {
  if(isAtEnd()) return false;

  return peek().type == type;
}

Token Parser::peek() { return tokens[current]; }

Token Parser::advance() {
  if (!isAtEnd()) current++;

  return previous();
}

Token Parser::previous() { return tokens[current - 1]; }

bool Parser::isAtEnd() {
  return peek().type == TokenType::EOFF;
}


void Parser::synchronize() {
  advance();

  while(!isAtEnd()) {
    if(previous().type == SEMICOLON) return;

    switch (peek().type) {
    case TokenType::CLASS:
    case TokenType::FUN:
    case TokenType::VAR:
    case TokenType::FOR:
    case TokenType::IF:
    case TokenType::WHILE:
    case TokenType::PRINT:
    case TokenType::RETURN:
      return;
    }
    advance();
  }
}
