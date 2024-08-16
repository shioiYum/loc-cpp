#include <any>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include "Token.hpp"
#include "Expr.hpp"
#include "ExprVisitor.h"
#include "TokenType.hpp"


class AbstractTreePrinter: ExprVisitor<std::any> {
public:
  std::string print(Expr& expr) {
    std::any val = expr.accept(*this);
    return std::any_cast<std::string>(val);
  }

  std::any visitBinaryExpr(const BinaryExpr& expr) override {
    return parenthesize(expr.getToken().lexeme, expr.getLeftExpr(), expr.getRightExpr());
  }

  std::any visitLiteralExpr(const LiteralExpr& expr) override {
    return parenthesize(stringify(expr.getLiteralValue()));
    }

    std::any visitGroupingExpr(const GroupingExpr& expr) override {
      return parenthesize("group", expr.getExpression());
    }

  std::any visitUnaryExpr(const UnaryExpr& expr) override {
    return parenthesize(expr.getToken().lexeme, expr.getRight());
  }

private:

  std::string stringify(const std::any& object) {
    if(!object.has_value()) {
      return "nil";
    }

    if(object.type() == typeid(bool)) {
      return std::any_cast<bool>(object) ? "true": "false";
    }

    if(object.type() == typeid(double)) {
      double n = std::any_cast<double>(object);
      if (std::trunc(n) == n) {
	return std::to_string((int) n);
      } else {
	return std::to_string(n);
      }
    }

    if (object.type() == typeid(std::string)) {
      return std::any_cast<std::string>(object);
    }
    return "";
  }
  
    template<typename... Args>
    std::string parenthesize(const std::string& name, const Args&... exprs){
        std::string result = "(" + name;
	((result += " " + stringify(exprs.accept(*this))), ...);
        result += ")";
        return result;
    }
};

int main() {
  Expr * expr = new BinaryExpr(std::unique_ptr<Expr>(new LiteralExpr(123.0)), Token(TokenType::MINUS, "-", 1), std::unique_ptr<Expr>(new LiteralExpr(123.0)));

  Expr * expr2 = new BinaryExpr(
				std::unique_ptr<Expr>(new UnaryExpr(
								    Token(TokenType::MINUS, "-", 1),
								    std::unique_ptr<Expr>(new LiteralExpr(123.0))
								    )),
				Token(TokenType::STAR, "*", 1),
				std::unique_ptr<Expr>(new GroupingExpr(
								       std::unique_ptr<Expr>(new LiteralExpr(45.67))
								       )
						      )
				);
  
  AbstractTreePrinter atp;
  std::cout << atp.print(*expr) << "\n";
  std::cout << atp.print(*expr2) << "\n";

}


