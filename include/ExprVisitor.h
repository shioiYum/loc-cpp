#ifndef EXPR_VISITOR_H
#define EXPR_VISITOR_H

class BinaryExpr;
class LiteralExpr;
class GroupingExpr;
class UnaryExpr;

template <typename T>
class ExprVisitor {
  public:
  ~ExprVisitor() = default;

  virtual T visitBinaryExpr(const BinaryExpr& expr);
  virtual T visitLiteralExpr(const LiteralExpr& expr);
  virtual T visitGroupingExpr(const GroupingExpr& expr);
  virtual T visitUnaryExpr(const UnaryExpr& expr);
};
#endif
