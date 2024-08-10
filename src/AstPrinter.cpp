#include <any>
#include <iostream>
#include <string>
#include "Expr.hpp"
#include "Literal.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

class AstPrinter : public Visitor<std::string>
{
public:
    template <typename T>
    std::string print(Expr<T>* expr)
    {
        return expr -> accept(*this);
    }

    std::string visit(Binary &expr) override
    {
      return parenthesize(expr.oper.lexeme, expr.left, expr.right);
    }

    std::string visit(Grouping &expr) override
    {
        return parenthesize("group", expr.expression);
    }

    std::string visit(Literal &expr) override
    {
      if(expr.value.type == LiteralData::DataType::EMPTY)
	{
	  return "nil";
	}

      if(expr.value.type == LiteralData::DataType::STRING) {
	return *static_cast<std::string*>(expr.value.value);
      }

      return std::to_string(*static_cast<int*>(expr.value.value));
    }

    std::string visit(Unary &expr) override
    {
        return parenthesize(expr.oper.lexeme, expr.right);
    }

private:

  std::string parenthesize_impl(std::string final_string)
  {
    return final_string + ")";
  }
  
  template <typename T, typename... Args>
  std::string parenthesize_impl(std::string final_string, Expr<T>& first, Args&... args )
  {
    final_string += " " + first -> accept(*this);
  }

  template <typename T, typename... Args>
  std::string parenthesize(std::string name, Expr<T> first, Args... args)
  {
    std::string final_string = "(" + name;
    final_string = parenthesize(final_string, first, args...);
    return final_string;
  }
};

int main()
{
  std::string minus = "-";
  std::string *minus_pointe = &minus;
  LiteralData minuSign(minus_pointe, LiteralData::DataType::STRING);

  int number123 = 123;
  int *number123_pointe = &number123;
  LiteralData intSign(number123_pointe, LiteralData::DataType::INT);

  Token token(TokenType::MINUS, "-", minuSign, 1);
  Expr<Literal> * lit = new  Literal(intSign);

  Expr<Unary> * exp = new Unary(token, lit);

  AstPrinter printer;
  // std::cout << printer.print(expression) << "\n";
  std::cout << printer.print(exp) << "\n";
  return 0;
}
