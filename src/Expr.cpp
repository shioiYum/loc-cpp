#include "Expr.hpp"
#include "Literal.hpp"
#include "Token.hpp"

Binary::Binary(Expr left, Token oper, Expr right): 
left(left), oper(oper), right(right) { }

Grouping::Grouping(Expr expression): 
expression(expression) { }

Literal::Literal(LiteralData value) : value(value) {}

Unary::Unary(Token oper, Expr* right): 
oper(oper), right(right) { }

