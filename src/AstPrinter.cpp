#include <any>
#include <cstdio>
#include <iostream>
#include <string>

#include "Token.hpp"
#include "Expr.hpp"
#include "ExprVisitor.h"


class AbstractTreePrinter: ExprVisitor<std::any> {
public:
  std::string print(Expr& expr) {
    return std::any_cast<std::string>(expr.accept(*this));
  }

  std::any visitBinaryExpr(const BinaryExpr& expr) override {
    return parenthesize(expr.getToken().lexeme, expr.getLeftExpr(), expr.getRightExpr());
  }

  std::any visitLiteralExpr(const LiteralExpr& expr) override {
      std::any literalValue = expr.getLiteralValue();
      if(literalValue.has_value())
	return "nil";

      return parenthesize(std::any_cast<std::string>(literalValue));
    }

    std::any visitGroupingExpr(const GroupingExpr& expr) override {
      return parenthesize("group", expr.getExpression());
    }

  std::any visitUnaryExpr(const UnaryExpr& expr) override {
    return parenthesize(expr.getToken().lexeme, expr.getRight());
  }

private:
    template<typename... Args>
    std::string parenthesize(const std::string& name, const Args&... exprs){
        std::string result = "(" + name;
        ((result += " " + std::any_cast<std::string>(exprs.accept(*this))), ...);
        result += ")";
        return result;
    }
};

int main() {
  Expr * expr = new LiteralExpr("12");
  AbstractTreePrinter atp;
  std::cout << atp.print(*expr) << "\n";

}

