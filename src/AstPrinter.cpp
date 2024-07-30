#include <iostream>
#include "Expr.hpp"

class AstPrinter : public Visitor<std::string>
{
public:
    template <typename T>
    std::string print(Expr<T> expr)
    {
        return expr.accept(*this);
    }

    std::string visit(Binary &expr)
    {
        return parenthesize(expr.oper.lexeme, expr.left, expr.right);
    }
    std::string visit(Grouping &expr)
    {
        return parenthesize("group", expr.expression);
    }
    std::string visit(Literal &expr)
    {
        if (!expr.value.has_value())
        {
            return "nil";
        }
        return std::any_cast<std::string>(expr.value);
    }
    std::string visit(Unary &expr)
    {
        return parenthesize(expr.oper.lexeme, expr.right);
    }

    template <typename T>
    std::string parenthesize(std::string name, Expr<T> exprs, ...)
    {
        std::string final_string = "(" + name;

        for (Expr<T> expr : exprs)
        {
            final_string + " ";
            final_string + exprs.accept(*this);
        }
        final_string + ")";

        return final_string;
    }
};
