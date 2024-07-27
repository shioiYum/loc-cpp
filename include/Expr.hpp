#ifndef EXPR_H
#define EXPR_H
#include "Token.hpp"

class Expr {
    public:
        virtual ~Expr() = default;
};


class Binary: public Expr {
    public:
        const Expr left;
        const Token oper;
        const Expr right;

        Binary(Expr left, Token oper, Expr right);
        
};

#endif