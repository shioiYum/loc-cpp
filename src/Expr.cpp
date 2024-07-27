#include "Expr.hpp"

Binary::Binary(Expr left, Token oper, Expr right): 
    left(left), oper(oper), right(right) {
        
    }

