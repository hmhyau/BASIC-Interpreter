#include "PrintCommand.h"
#include "Operand.h"
#include <iostream>
#include <stdexcept>


// PrintCommand.cpp. Contains PrintCommand command member functions.

const std::string PrintCommand::Operation = "PRINT";

// Inputs "PRINT" command line string. Identifies if the target is an Operand or string.
// Locates '"' in string with begin() and rbegin() functions;
// if only one '"' is detected, throws an exception.
PrintCommand::PrintCommand (std::istringstream& line, Program& program){
    std::string string;
    std::getline(line, string);
    string = string.substr(string.find_first_not_of(' '), string.find_last_not_of(" \r\n")-string.find_first_not_of(' ')+1);

    if((*string.begin() == '"' && *string.rbegin() != '"') || (*string.begin()!= '"' && *string.rbegin() == '"'))
    throw std::invalid_argument { ("Invalid print operand: " + string) };
    if((*string.begin() == '"') && (*string.rbegin() == '"')){
        _isString = true;
        new (&String) std::string (string.substr (string.find_first_of('"') + 1, string.find_last_of('"') - 1));
        
        size_t pos = 1;
        while ((pos = String.find("\\n", pos-1)) != std::string::npos)
            String.replace (pos, 2, "\n");
    }
    else{
        _isString = false;
        new (&Variable) Operand(string, program);
    }
}

// Calling destructor conditionally if either string or variable target.
PrintCommand::~PrintCommand () {
    if (_isString)
        String.~basic_string<char>();
    else
        Variable.~Operand();
}

// Prints target to output. 
bool PrintCommand::Execute () {
    if (_isString)
        std::cout << String;
    else
        std::cout << Variable;
    return true;
}
