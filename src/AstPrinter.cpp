#include <any>
#include <iostream>
#include "Expr.hpp"

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
        if(expr.value.has_value()){
            std::string value =  std::any_cast<std::string>(expr.value);
            std::cout << value << "\n";
        }

        return "";
    }

    std::string visit(Unary &expr) override
    {
        return parenthesize(expr.oper.lexeme, expr.right);
    }

private:
    template <typename T>
    std::string parenthesize(std::string name, Expr<T> exprs, ...)
    {
        std::string final_string = "(" + name;
        return final_string;
    }
};

int main()
{   
    Expr<Literal> * expression = new Literal(12);
    AstPrinter printer;
    std::cout << printer.print(expression) << "\n";
    return 0;
}
