#include "Expr.hpp"
#include "Token.hpp"

Expr::Binary::Binary(Expr left, Token oper, Expr right) : 
left(left), oper(oper), right(right) {}

Expr::Grouping::Grouping(Expr expression) : 
expression(expression) {}
