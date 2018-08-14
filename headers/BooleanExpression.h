#pragma once
#include "Expression.h"

// BooleanExpression.h. Derived calss of Expression.
class BooleanExpression : protected Expression<bool> {
public:
    static const std::string Operators;
    
// Enumerated class of select operators.
private:
    enum class Operator { Equal, GreaterThan, LessThan } _operator;

// Principle function with BASIC command line as input string and reference to program.
public:
    BooleanExpression (std::istringstream& line, Program& program);
    
    bool Evaluate () const override;
};

