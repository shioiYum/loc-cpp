#include "Expr.hpp"
#include "ExprVisitor.h"
#include "Token.hpp"
#include <any>
#include <cstdio>
#include <memory>

//For Binary Expression

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op,
                       std::unique_ptr<Expr> right)
    : left(std::move(left)), op(op), right(std::move(right)){};


std::any BinaryExpr::accept(ExprVisitor<std::any> &visitor) const  {
  return visitor.visitBinaryExpr(*this);
}

// for groupingexpr

GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)){};

std::any GroupingExpr::accept(ExprVisitor<std::any> &visitor) const {
  return visitor.visitGroupingExpr(*this);
}

// For literalexpr

LiteralExpr::LiteralExpr(std::any value) : value(value){};


std::any LiteralExpr::accept(ExprVisitor<std::any> &visitor) const{
  return visitor.visitLiteralExpr(*this);
}

// for unaryexpr

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right)
    : op(op), right(std::move(right)){};

std::any UnaryExpr::accept(ExprVisitor<std::any> &visitor) const {
  return visitor.visitUnaryExpr(*this);
}
