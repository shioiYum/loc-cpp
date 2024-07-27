#ifndef EXPR_H
#define EXPR_H
#include "Token.hpp"

class Expr
{
public:
    virtual ~Expr() = default;
};

class Binary : public Expr
{
public:
    const Expr left;
    const Token oper;
    const Expr right;
    Binary(Expr left, Token oper, Expr right);
};

class Grouping : public Expr
{
public:
    const Expr expression;
    Grouping(Expr expression);
};

class Literal : public Expr
{
public:
    const std::any value;
    Literal(std::any value);
};

class Unary : public Expr
{
public:
    const Token oper;
    const Expr right;
    Unary(Token oper, Expr right);
};

#endif
