#pragma once
#include "Command.h"

// EndIfCommand.h. Derived class of Command.
class EndIfCommand : public Command {
public:
    static const std::string Operation;

public:
    explicit EndIfCommand () = default;

    bool Execute () override;
};

