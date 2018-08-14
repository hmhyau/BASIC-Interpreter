#include "InputCommand.h"
#include <iostream>


// InputCommand.cpp. Contains InputCommand member functions.
const std::string InputCommand::Operation = "INPUT";

// Initialising the variable according to the operand constructor.
InputCommand::InputCommand (std::istringstream& line, Program& program)
    : _Variable { line, program } {}

// Reads input variable. 
bool InputCommand::Execute () {
    std::cin >> _Variable;
    return true;
}
