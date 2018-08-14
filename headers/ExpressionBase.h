#pragma once
#include "Operand.h"
#include <sstream>

// ExpressionBase.h. Base class of related Expression classes. Inputs operation string
// and extracts the operator and the two sujects of the calculation.

class ExpressionBase {
protected:
    Operand _lhs;
    Operand _rhs;
    char _operatorString;

public:
    ExpressionBase (std::istringstream& line, Program& program);
    virtual ~ExpressionBase () = default;

    
// Private constructor definitions to be delegated by the public constructor ExpressionBase.
private:
    ExpressionBase (Operand&& lhs, std::istringstream& line, Program& program);
    ExpressionBase (Operand&& lhs, char op, std::istringstream& line, Program& program);
};

