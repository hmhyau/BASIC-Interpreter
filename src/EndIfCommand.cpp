#include "EndIfCommand.h"


// EndIfCommand.cpp. Inputs EndIf BASIC line string. Returns true if ENDIF is detected.

const std::string EndIfCommand::Operation = "ENDIF";

bool EndIfCommand::Execute () {
    return true;
    
}
