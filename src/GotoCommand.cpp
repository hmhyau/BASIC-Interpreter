#include "GotoCommand.h"
#include "Program.h"


//GotoCommand.cpp. Contains GotoCommand member functions.

const std::string GotoCommand::Operation = "GOTO";

// Inputs GOTO BASIC line as string. Identifies target line number.
GotoCommand::GotoCommand (std::istringstream& line, Program& program)
: _program { program }
, _tgtLineNum{0} { line >> _tgtLineNum; }

// Inputs target line numeber. Sets the program iterator to line number
// specified by _tgtLineNum. 
bool GotoCommand::Execute () {
    _program.SetNextLine(_tgtLineNum);
    return false;
}
