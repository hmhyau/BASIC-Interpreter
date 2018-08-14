#pragma once
#include "Expression.h"
#include "Value.h"

// ArithmeticExpression.h. Derived from Expression with protected access
// and from Value with public access.

class ArithmeticExpression : protected Expression<double>, public Value {
public:
    static const std::string Operators; 

// Enumerated class of operators.
private:
    enum class Operator { Add, Subtract, Multiply, Divide } _operator; 

// Constructor of ArithmeticExpression.
public:
    ArithmeticExpression (std::istringstream& line, Program& program);

// Protected accessor functions inherited from Expression.
protected:
    double Evaluate () const;
    double Get () const;
};

