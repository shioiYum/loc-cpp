#ifndef EXPR_H
#define EXPR_H
#include "Token.hpp"
#include <iostream>

template <typename T> class Visitor;

class Expr {
public:
  class Binary;
  class Grouping;

  virtual ~Expr() = default;

  template <typename T>
  T accept(Visitor<T>& visitor){
    return T(); 
  }
};

template <typename T>
class Visitor {
public:
  virtual T visitBinary(Expr::Binary &binary) = 0;
  virtual T visitGrouping(Expr::Grouping &grouping) = 0;
};

// Nested class
class Expr::Binary: public Expr {
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

class Expr::Grouping: public Expr {
public:
  const Expr expression;

  Grouping(Expr expression);
   template <typename T>
  T accept(Visitor<T>& visitor) {
     return visitor.visitGrouping(*this);
     }
};
#endif
