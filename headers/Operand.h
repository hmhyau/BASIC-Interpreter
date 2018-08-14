#pragma once
#include "Value.h"
#include <string>
#include <sstream>


// Operand.h. Derived class of Value.
class Program;

class Operand : public Value {
private:
    Program& _program;
    bool _isConst;
    union{
        double Const;
        std::string VarName;
    };

public:
    Operand (std::istringstream& line, Program& program);
    Operand (std::string const& operand, Program& program);
    Operand (Operand&& other) noexcept;
    virtual ~Operand ();

    Operand& operator=(Operand&& other) noexcept;
    Operand& operator=(Value const& other);

    friend std::istream& operator>>(std::istream& stream, Operand& obj);
    friend std::ostream& operator<<(std::ostream& stream, Operand const& obj);

//  Overloaded operators for Operand class.
    double operator*(Operand const& rhs) const;
    double operator/(Operand const& rhs) const;
    double operator+(Operand const& rhs) const;
    double operator-(Operand const& rhs) const;

    bool operator==(Operand const& rhs) const;
    bool operator>(Operand const& rhs) const;
    bool operator<(Operand const& rhs) const;

protected:
    double Get () const override;

private:
    double& Get ();
};
