#include "LetCommand.h"
#include "ArithmeticExpression.h"


// LetCommand.cpp. Contains LetCommand member functions.

const std::string LetCommand::Operation = "LET";

// Inputs "Let" BASIC command line string. Checks if string has valid format.
// Depending on the string, creates a unique pointer of class Value
// which holds either an ArithmeticExpression or an Operand variable.
LetCommand::LetCommand (std::istringstream& line, Program& program)
:_Variable(line, program){
    char assignment;
    line >> std::ws;
    line >> assignment;
    if (assignment != '=')
        throw std::invalid_argument { ("Incorrect assignment: " + std::string(1, assignment))};
    
    std::string expr;
    std::getline(line, expr);
    if(expr.find_first_of("+-") != 0 && expr.find_first_of(ArithmeticExpression::Operators) != std::string::npos){
        std::istringstream exprStream { expr };
        _Value = std::make_unique<ArithmeticExpression> (exprStream, program);
    } else{
        _Value = std::make_unique<Operand> (expr, program);
    }
}

// Appoints Operand _Varible specified by the dereferenced value.
bool LetCommand::Execute () {
    _Variable = *_Value;
    return true;
}
