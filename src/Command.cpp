#include "Command.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "GotoCommand.h"
#include "InputCommand.h"
#include "LetCommand.h"
#include "EndIfCommand.h"

#include <sstream>

// Command.cpp. Inputs string containing line of BASIC input program.
// Extracts the linenumber and the command, which is then designated to relevant derived command classes
// and creates a std::pair consisting of the line number and a unique pointer to the command.
// Rethrows exceptions which occurs in subsequent call stacks, and throw an exception when the command is not supported.

std::pair<unsigned, std::unique_ptr<Command>> Command::Create (std::string const& line, Program& program, std::stack<IfCommand*>& ifTracker) {
    std::istringstream ss { line };
    
    unsigned linenum;
    std::string operation;
    ss >> linenum >> operation;
    
    try{
        if (operation == PrintCommand::Operation)
            return { std::make_pair(linenum, std::make_unique<PrintCommand>( ss, program )) };
        
        else if (operation == GotoCommand::Operation)
            return { std::make_pair(linenum, std::make_unique<GotoCommand>( ss, program )) };
    
        else if (operation == InputCommand::Operation)
            return { std::make_pair(linenum, std::make_unique<InputCommand>( ss, program )) };
        
        else if (operation == LetCommand::Operation)
            return { std::make_pair(linenum, std::make_unique<LetCommand>( ss, program )) };
        
        else if (operation == IfCommand::Operation){
            auto cmd = std::make_unique<IfCommand>( ss, program );
            ifTracker.push(cmd.get());
            return std::make_pair(linenum, std::move(cmd));
        }
        
        else if (operation == EndIfCommand::Operation){
            if(ifTracker.empty())
                throw std::runtime_error { ("Incomplete IF stack" ) };
            ifTracker.top() -> EndIf(linenum);
            ifTracker.pop();
            return std::make_pair(linenum, std::make_unique<EndIfCommand> ());
        }
    }
    catch (std::exception const& e) {
        throw std::invalid_argument { (std::string(e.what()) + " (" + std::to_string(linenum) +")" ) };
    }
    
    throw std::invalid_argument{ ("Operation '" + operation + "' is not supported (" + std::to_string (linenum) + ")").c_str () };
}
