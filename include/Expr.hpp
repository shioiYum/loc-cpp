#ifndef EXPR_H
#define EXPR_H
#include "Token.hpp"
#include <iostream>

template <typename T> class Visitor;

class Expr { 
public:
class Binary;
class Grouping;
class Literal;
class Unary;

virtual ~Expr() = default;
template <typename T>
T accept(Visitor<T>& visitor){
return T(); 
}
};

template <typename T>
class Visitor {
public:
virtual T visitBinary(Expr::Binary &visitor) = 0;
virtual T visitGrouping(Expr::Grouping &visitor) = 0;
virtual T visitLiteral(Expr::Literal &visitor) = 0;
virtual T visitUnary(Expr::Unary &visitor) = 0;
};

class Binary: public Expr{ 
public:
const Expr left;
const Token oper;
const Expr right;
Binary(Expr left, Token oper, Expr right);
template <typename T>
T accept(Visitor<T>& visitor) { 
return visitor.visitBinary(*this);
}
};

class Grouping: public Expr{ 
public:
const Expr expression;
Grouping(Expr expression);
template <typename T>
T accept(Visitor<T>& visitor) { 
return visitor.visitGrouping(*this);
}
};

class Literal: public Expr{ 
public:
const std::any value;
Literal(std::any value);
template <typename T>
T accept(Visitor<T>& visitor) { 
return visitor.visitLiteral(*this);
}
};

class Unary: public Expr{ 
public:
const Token oper;
const Expr right;
Unary(Token oper, Expr right);
template <typename T>
T accept(Visitor<T>& visitor) { 
return visitor.visitUnary(*this);
}
};

#endif
