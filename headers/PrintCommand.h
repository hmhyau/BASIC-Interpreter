#pragma once
#include "Command.h"
#include "Operand.h"
#include <sstream>

// PrintCommand.h. Derived class of Command.
class PrintCommand : public Command {
public:
    static const std::string Operation;

private:
    bool _isString;
    union{
        std::string String;
        Operand Variable;
    };

// Principle function with BASIC command line as input string and reference to program.
public:
    PrintCommand (std::istringstream& line, Program& program);
    virtual ~PrintCommand (); 

    bool Execute () override;
};

