#pragma once
#include <string>
#include <stack>
#include <memory>

class Program;
class IfCommand;

// Command.h. Base class for all command classes.
class Command {
public:
    static std::pair<unsigned, std::unique_ptr<Command>> Create (std::string const& line, Program& program, std::stack<IfCommand*>& ifTracker);

public:
    virtual ~Command () = default; 

    virtual bool Execute () = 0;

protected:
    Command () = default;

};

