#include "BooleanExpression.h"
#include <stdexcept>


// BooleanExpression.cpp. Contains BooleanExpression member functions

// Static constant string which defines the supported boolean expressions.
const std::string BooleanExpression::Operators = "=><";

// Inputs BASIC logic expression as string. Identifies what operator is being called with switch function.
BooleanExpression::BooleanExpression (std::istringstream& line, Program& program)
: Expression {line, program}{
    switch (_operatorString) {
        case '=':
            _operator = Operator::Equal;
            break;
        case '>':
            _operator = Operator::GreaterThan;
            break;
        case '<':
            _operator = Operator::LessThan;
            break;
        default:
            throw std::invalid_argument { ("Operator '" + std::string(1, _operatorString) + "' is not supported in BooleanExpression").c_str() };
    }
}

// Executes the boolean expression when the command in question is executed by the main program.
bool BooleanExpression::Evaluate () const {
    switch (_operator) {
        case Operator::Equal:
            return _lhs == _rhs;
        case Operator::GreaterThan:
            return _lhs > _rhs;
        case Operator::LessThan:
            return _lhs < _rhs;
    }
    throw std::invalid_argument { ("BooleanExpression Operator is invalid") };
}
