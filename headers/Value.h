#pragma once

// Value.h. Abstract class with methods to be overriden by either
// the Operand class or ArithmeticExpression class.

class Value {
public:
    virtual ~Value () = default;

    virtual double Get () const = 0;
};

