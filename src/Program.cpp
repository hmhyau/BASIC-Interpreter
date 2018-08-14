#include "Program.h"
#include "Command.h"
#include "IfCommand.h"

#include <stack>
#include <fstream>
#include <iostream>


// Program.cpp. Reads BASIC input program.

// Performs error checking to ensure file is valid. Iterates through input file and line by
// line, each line creates a std::pair container entry which includes
// the line number and a unique pointer to the command.
// The pair is then stored into a map container _program.
// At the end of the constructor, initialise the iterator _iterator of _program.
Program::Program (std::string const& filename) {
    std::ifstream file(filename, std::ifstream::in);
    if(file.fail())
        throw std::ios_base::failure{ ("File" + filename + "does not exist") };
    if(file.peek() == std::ifstream::traits_type::eof())
        throw std::invalid_argument{ ("File" + filename + "is empty") };
    
    std::stack<IfCommand *> IfTracker;
    
    while(!file.eof()){
        std::string line;
        std::getline (file, line);
        
        if(line.length() == 0)
            continue;
        
        auto cmd = Command::Create(line, *this, IfTracker);
        auto _iter = _program.insert (std::move(cmd)) ;
        if(std::next(_iter.first) != _program.end())
            throw std::runtime_error { ("Inconsistent linenumbers: (" + std::to_string(_iter.first->first) + ")") };
    }
    _iterator = _program.begin();
    
}

// Run the program. Catch any exception during execution,
// otherwise iterate until the end of _iterator.
void Program::Run () {
    while (_iterator != _program.end()){
        try{
            const bool advance = _iterator->second->Execute();
            if(advance)
                ++_iterator;
        } catch (std::exception const& e){
            throw std::invalid_argument { (std::string (e.what()) + " (" + std::to_string (_iterator->first) + ")").c_str() };
        }
    }
}

// Change iterator pointer to the targeted command specified by linenumber.
void Program::SetNextLine (const unsigned linenumber) {
    _iterator = _program.find(linenumber);
    if (_iterator == _program.end())
        throw std::runtime_error { ("Line number (" + std::to_string(linenumber) +  ") is not found") };
}

