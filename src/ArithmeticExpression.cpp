#include "ArithmeticExpression.h"
#include <stdexcept>

// ArithmeticExpression.cpp. Contains ArithmeticExpression member functions.

// Static constant string which defines the supported arithmetic expressions.
const std::string ArithmeticExpression::Operators = "+-*/";

// Constructor. It calls the constructor of Expression which in turn calls the constructor of ExpressionBase.
// The operator is evaluated from _operatorString and is assigned to the appropriate operator in enum class Operator
// using a switch-case.

ArithmeticExpression::ArithmeticExpression (std::istringstream& line, Program& program)
: Expression(line, program){
    switch (_operatorString) {
        case '+':
            _operator = Operator::Add;
            break;
        case '-':
            _operator = Operator::Subtract;
            break;
        case '*':
            _operator = Operator::Multiply;
            break;
        case '/':
            _operator = Operator::Divide;
            break;
        default:
            throw std::invalid_argument { ("Operator '" + std::string(1, _operatorString) + "' is not supported in ArithmeticExpression").c_str() };
    }
}

// Evalute the arithmetic expression when the command in question is executed by the main program.
double ArithmeticExpression::Evaluate () const {
    switch (_operator) {
        case Operator::Add:
            return _lhs + _rhs;
        case Operator::Subtract:
            return _lhs - _rhs;
        case Operator::Multiply:
            return _lhs * _rhs;
        case Operator::Divide:
            return _lhs / _rhs;
    }
    throw std::invalid_argument { "ArithmeticExpression Operator is invalid" };
}

// Accessor. Calls ArithmeticExpression::Evaluate().
double ArithmeticExpression::Get () const {
    return Evaluate();
}
