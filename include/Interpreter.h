#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Expr.hpp"
#include "ExprVisitor.h"
#include <any>

class Interpreter : ExprVisitor<std::any> {
public:
  std::any visitLiteralExpr(const LiteralExpr& expr) override;
  std::any visitBinaryExpr(const BinaryExpr& expr) override;
  std::any visitGroupingExpr(const GroupingExpr& expr) override;
  std::any visitUnaryExpr(const UnaryExpr& expr) override;

  std::any evalute(const Expr& expr);

private:
  bool isTruthy(std::any& object);
  bool isEqual(std::any& object, std::any& object2);
};


#endif // INTERPRETER_H
