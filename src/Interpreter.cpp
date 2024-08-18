#include "Interpreter.h"
#include "TokenType.hpp"
#include <any>
#include <cstdio>
#include <string>


std::any Interpreter::visitLiteralExpr(const LiteralExpr &expr) {
  return expr.getLiteralValue();
}

std::any Interpreter::visitGroupingExpr(const GroupingExpr &expr) {
  return evalute(expr.getExpression());
}

std::any Interpreter::visitUnaryExpr(const UnaryExpr &expr) {
  std::any right = evalute(expr.getRight());

  switch (expr.getToken().type) {
  case TokenType::MINUS:
    return -std::any_cast<double>(right);

  case TokenType::BANG:
    return !isTruthy(right);

  default:
    return NULL;
  }

}


std::any Interpreter::visitBinaryExpr(const BinaryExpr &expr) {
  std::any left = evalute(expr.getLeftExpr());
  std::any right = evalute(expr.getRightExpr());

  switch (expr.getToken().type) {
  case TokenType::GREATER:
    return std::any_cast<double>(left) > std::any_cast<double>(right);

  case TokenType::LESS:
    return std::any_cast<double>(left) < std::any_cast<double>(right);

  case TokenType::GREATER_EQUAL:
    return std::any_cast<double>(left) >= std::any_cast<double>(right);
    
  case TokenType::LESS_EQUAL:
    return std::any_cast<double>(left) <= std::any_cast<double>(right);

  case TokenType::MINUS:
    return std::any_cast<double>(left) - std::any_cast<double>(right);

  case TokenType::SLASH:
    return std::any_cast<double>(left) / std::any_cast<double>(right);

  case TokenType::STAR:
    return std::any_cast<double>(left) * std::any_cast<double>(right);

  case TokenType::BANG_EQUAL:
    return !isEqual(left, right);

  case TokenType::EQUAL_EQUAL:
    return isEqual(left, right);    

  case TokenType::PLUS:
    if(left.type() == typeid(double) && right.type() == typeid(double)) {
      return std::any_cast<double>(left) + std::any_cast<double>(right);
    }

    if(left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
      return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
    }
    break;
    
  default:
    return NULL;
  }

  return NULL;

}



std::any Interpreter::evalute(const Expr &expr) { return expr.accept(*this); }


bool Interpreter::isTruthy(std::any& object) {
  if(!object.has_value()) {
    return false;
  }

  if(object.type() == typeid(bool)) {
    return std::any_cast<bool>(object);
  }

  return true;
}

bool Interpreter::isEqual(std::any& object1, std::any& object2) {
  if(!object1.has_value() && !object2.has_value()) return true;

  if(!object1.has_value()) return false;

  if (object1.type() != object2.type()) {
    return false;
  }
    
  if (object1.type() == typeid(double)) {
    return std::any_cast<double>(object1) == std::any_cast<double>(object2);
    }
    
    
  if (object1.type() == typeid(std::string)) {
    return std::any_cast<std::string>(object1) == std::any_cast<std::string>(object2);
  }

  return false;

}

