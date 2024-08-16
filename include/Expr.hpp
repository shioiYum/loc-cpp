#ifndef EXPR_H
#define EXPR_H

#include "Token.hpp"
#include <any>
#include <iostream>
#include <memory>
#include "ExprVisitor.h"

class Expr
{
public:
  virtual ~Expr() = default;

  virtual std::any accept(ExprVisitor<std::any>& visitor) const = 0;
};

class BinaryExpr: public Expr {
  public:
  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
  std::any accept(ExprVisitor<std::any>& visitor) const override;

  const Expr& getLeftExpr() const { return *left; }
  const Token getToken() const {return op; }
  const Expr& getRightExpr() const { return *right; }
  private:
  std::unique_ptr<Expr> left;
  Token op;
  std::unique_ptr<Expr> right;
};

class GroupingExpr: public Expr {
  public:
  GroupingExpr(std::unique_ptr<Expr> expression);
  std::any accept(ExprVisitor<std::any>& visitor) const override;

  const Expr& getExpression() const{ return *expression;}
  private:
  std::unique_ptr<Expr> expression;
};

class LiteralExpr: public Expr {
public:
  LiteralExpr(std::any value);
  std::any accept(ExprVisitor<std::any> &visitor) const override;

  const std::any& getLiteralValue() const {return value; }
  
  private:
  std::any value;
};

class UnaryExpr: public Expr {
public:
  UnaryExpr(Token op, std::unique_ptr<Expr> right);
  std::any accept(ExprVisitor<std::any> &visitor) const override;

  Token getToken() const { return op;}
  const Expr& getRight() const  { return *right; }
private:
  Token op;
  std::unique_ptr<Expr> right;
};

#endif
