#pragma once
#include "Command.h"
#include "Operand.h"
#include <sstream>

// InputCommand.h. Derived class of Command.
class InputCommand : public Command {
public:
    static const std::string Operation;

private:
    Operand _Variable;

// Principle function with BASIC command line as input string and reference to program. 
public:
    InputCommand (std::istringstream& line, Program& program);

    bool Execute () override;
};

