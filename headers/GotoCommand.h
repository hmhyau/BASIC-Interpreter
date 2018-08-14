#pragma once
#include "Command.h"
#include <sstream>

//GotoCommand.h. Derived class of Command.
class GotoCommand : public Command {
public:
    static const std::string Operation;

private:
    Program& _program;
    unsigned _tgtLineNum;

// Principle function with BASIC command line as input string and reference to program. 
public:
    GotoCommand (std::istringstream& line, Program& program);

    bool Execute () override;
};

