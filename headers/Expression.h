#pragma once
#include "ExpressionBase.h"

// ExpressionBase.h. Templated Expression class. It is an abstraction for the BooleanExpression
// and ArithmeticExpression type classes.
template <typename T>
class Expression : protected ExpressionBase {
public:
    Expression (std::istringstream& line, Program& program);
    virtual ~Expression () = default;

    virtual T Evaluate () const = 0;
};

#pragma region Implementation
// Expression is a derived class of ExpressionBase. This is calling the ExpressionBase class constructor.
template <typename T>
Expression<T>::Expression (std::istringstream& line, Program & program)
: ExpressionBase { line, program } {}

#pragma endregion

