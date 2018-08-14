#include "IfCommand.h"
#include "Program.h"


// IfCommand.cpp. Contains IfCommand member functions. 

const std::string IfCommand::Operation = "IF";

// Inputs "If" BASIC command line string. Checks if string has valid format. Returns
// to Program.cpp to read conditional operation within function. 
IfCommand::IfCommand (std::istringstream& line, Program& program)
:_program { program }, _boolexpr{line, program}, _EndIfline{0}{
    std::string token;
    std::getline(line, token);
    
    if(token.find("THEN") == std::string::npos)
        throw std::invalid_argument{ "THEN is not found" };
}

// Outputs error if no End if statement. Store subsequent commands
// in the std::stack container declared in the base Command class.
// If ENDIF command is not found within the BASIC program,
// throws an exception.
bool IfCommand::Execute () {
    if (_EndIfline == 0)
        throw std::runtime_error { ("EndIf Command is not found") };
    
    if (!_boolexpr.Evaluate())
        _program.SetNextLine(_EndIfline);
    return true;
}

// Initialise _EndIfline variable upon execution of EndIf statement.
void IfCommand::EndIf (const unsigned linenumber) {
    _EndIfline = linenumber;
}
