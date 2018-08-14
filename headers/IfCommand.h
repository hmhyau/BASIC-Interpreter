#pragma once
#include "Command.h"
#include "BooleanExpression.h"
#include <sstream>

//IfCommand.h. Derived class of Command.
class IfCommand : public Command {
public:
    static const std::string Operation;

// Private variables and objects.
private:
    Program& _program;
    BooleanExpression _boolexpr;
    unsigned _EndIfline;

public:
    // Principle function with BASIC command line as input string and reference to program. 
    IfCommand (std::istringstream& line, Program& program);
    void EndIf (unsigned linenumber);

    bool Execute () override;
};

