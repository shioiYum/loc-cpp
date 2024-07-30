#ifndef EXPR_H
#define EXPR_H
#include "Token.hpp"
#include <iostream>

template <typename T>
class Visitor;


template <typename T>
class Expr
{
public:
    class Binary;
    class Grouping;
    class Literal;
    class Unary;

    virtual ~Expr() = default;
    template <typename R>
    auto accept(Visitor<R> &visitor) {
        return visitor.visit(*static_cast<T*>(this));
    }
};

template <typename T>
class Visitor
{
public:
    virtual T visit(Binary &visitor) = 0;
    virtual T visit(Grouping &visitor) = 0;
    virtual T visit(Literal &visitor) = 0;
    virtual T visit(Unary &visitor) = 0;
};

class Binary : public Expr<Binary>
{
public:
    const Expr left;
    const Token oper;
    const Expr right;
    Binary(Expr left, Token oper, Expr right);
    template <typename T>
    T accept(Visitor<T> &visitor)
    {
        return visitor.visitBinary(*this);
    }
};

class Grouping : public Expr<Grouping>
{
public:
    const Expr expression;
    Grouping(Expr expression);
    template <typename T>
    T accept(Visitor<T> &visitor)
    {
        return visitor.visitGrouping(*this);
    }
};

class Literal : public Expr<Literal>
{
public:
    const std::any value;
    Literal(std::any value);
    template <typename T>
    T accept(Visitor<T> &visitor)
    {
        return visitor.visitLiteral(*this);
    }
};

class Unary : public Expr<Unary>
{
public:
    const Token oper;
    const Expr right;
    Unary(Token oper, Expr right);
    template <typename T>
    T accept(Visitor<T> &visitor)
    {
        return visitor.visitUnary(*this);
    }
};

#endif
