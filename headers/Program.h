#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "Command.h"

// Program.h. Base Class Program declaration.
class Program {
private:
    std::map<unsigned, std::unique_ptr<Command> > _program;
    std::unordered_map<std::string, double> _state;
    decltype(_program)::iterator _iterator;

public:
    explicit Program (std::string const& filename);
    
    void Run ();
    inline double const& operator[](std::string const& name) const;
    inline double& operator[](std::string const& name);

    void SetNextLine (unsigned linenumber);
};

#pragma region Implementation

// Inline functions //
// Overloaded [] operator to fetch the content of variable in
// the unordered_map _state specified by name.
// If the variable does not exist in the map, throws an exception.
// Otherwise, return the variable content.
double const& Program::operator[](std::string const& name) const{
    const auto elem = _state.find(name);
    if (elem == _state.end())
        throw std::invalid_argument (("Variable '" + name + "' is undefined").c_str());
    return elem->second;
}

// Creates a new entry in the unordered_map _state.
double& Program::operator[](std::string const& name){
    return _state[name];
}

#pragma endregion
