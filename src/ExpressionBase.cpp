#include "ExpressionBase.h"
#include "Program.h"

// ExpressionBase.h. ExpressionBase is the base class for Expression related classes.
// Saves the input sting as a local sting, token. It finds the position of the operator
// and outputs the char value asscociated with this position.
namespace {
    char ReadOperator (std::istringstream& line){
        std::string token;
        line >> token;
        const auto pos = token.find_first_of("+-*/><=");
        line.seekg(pos - token.length() + 1, std::ios_base::cur);
        return token[pos];
    }
}

//Constructor delegation of ExpressionBase, fetching the first argument of an expression
ExpressionBase::ExpressionBase (std::istringstream& line, Program& program)
: ExpressionBase(Operand{line, program}, line, program) {}

// First constructor delegation of ExpressionBase, transfers the argument from the previous constuctor to another
// operand target and reads the operator of the expresssion
ExpressionBase::ExpressionBase (Operand&& lhs, std::istringstream& line, Program& program)
: ExpressionBase(std::move(lhs), ReadOperator(line), line, program) {}

// Second constructor delegation of ExpressionBase, moves the rvalue reference with lhs expression to
// the protected member Operand vairable _lhs. Then, reads the remaining content of line and fetch the third argument
// of the expression, which is stored into protected member Operand variable _rhs.
// Finally, stores the operator into protected char variable _operatorString.
ExpressionBase::ExpressionBase (Operand&& lhs, const char op, std::istringstream& line, Program& program)
: _lhs{ std::move(lhs) }, _rhs{line, program}, _operatorString {op} {}
