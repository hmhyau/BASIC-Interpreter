#pragma once
#include "Command.h"
#include "Operand.h"
#include <memory>
#include <sstream>

// LetCommand.h. Derived class of Command.
class LetCommand : public Command {
public:
    static const std::string Operation;

private:
        Operand _Variable;
        std::unique_ptr<Value> _Value;
    
/* Principle function with BASIC command line as input string and reference to program. */
public:
    LetCommand (std::istringstream& line, Program& program);

    bool Execute () override;
};
