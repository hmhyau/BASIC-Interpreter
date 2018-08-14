#include "Operand.h"
#include "Program.h"

// An anonymous namespace containing ReadOperand function.
// ReadOperand accepts a reference to stringstream line, extracts the required operand contents
// and return it to the constructor of Operand class.
namespace {
    std::string ReadOperand (std::istringstream& line){
        std::string string;
        line >> std::ws;
        size_t beforePos = line.tellg();
        std::getline(line, string);
        
        size_t pos;
        if (((pos = string.find_first_of("+-*/=><")) != std::string::npos) && (string.find_first_of("+-*/=><)") == 0 || string.find_last_of("+-*/=><)") == string.length()-1))
            throw std::runtime_error { "Invalid Expression: " + string };
        string = string.substr(0, pos);
        
        // Somehow seekg does not clear eofbit automatically [C++11 Spec]
        line.clear();
        line.seekg(beforePos+pos);
        string = string.substr(0, string.find_first_of(" \\n"));
        return string;
    }
}

// Constructor of Operand.
Operand::Operand (std::istringstream& line, Program& program)
    : Operand(ReadOperand(line), program){
}

// Constructor delegation from Operand(std::istringstream&, Program&).
// Evaluate the operand returned from ReadOperand and deduce its variable type,
// which is then allocated with memory using placement new.
Operand::Operand (std::string const& operand, Program& program)
    : _program { program } {
    char *end;
    const double value = std::strtod(operand.c_str(), &end);
        
    if (end != std::addressof (*operand.begin ()) && end != std::addressof (*operand.rbegin ()) + 1)
        throw std::runtime_error { ("Invalid variable name: " + operand) };
    
    if (end != std::addressof (*operand.rbegin ()) + 1) {
        _isConst = false;
        new (&VarName) std::string(operand);
    } else{
        _isConst = true;
        new(&Const) double (value);
    }
}

// Move constructor. Takes a rvalue reference of type Operand, deduce its variable type
// which is then allocated with memory using placement new.
Operand::Operand (Operand&& other) noexcept
    : _program {other._program},
      _isConst(other._isConst){
    if(_isConst)
        new (&Const) double (other.Const);
    else
        new (&VarName) std::string(std::move(other.VarName));
}

// Explicitly defined destructor so that the correct memory is destroyed.
Operand::~Operand () {
    if(!_isConst)
        VarName.~basic_string<char>();
}

// Move assginment operator to transfer temporary Operand object to existing one.
Operand& Operand::operator= (Operand&& other) noexcept {
    this->_isConst = other._isConst;
    this->_program = std::move(other._program);
    if(_isConst)
        Const = other.Const;
    else
        VarName = std::move(other.VarName);
    return *this;
}

// Overloaded = operator to assign a value to input reference to Value other.
Operand& Operand::operator= (Value const& other) {
    if(_isConst)
        throw std::invalid_argument("Cannot assign to integral value");
    Get() = other.Get();
    return *this;
}

// Overloaded * operator for multiplication between two Operand variables.
double Operand::operator* (Operand const& rhs) const {
    return Get() * rhs.Get();
}

// Overloaded / operator for division between two Operand variables.
double Operand::operator/ (Operand const& rhs) const {
    return Get() / rhs.Get();
}

// Overloaded + operator for addition between two Operand variables.
double Operand::operator+ (Operand const& rhs) const {
    return Get() + rhs.Get();
}

// Overloaded - operator for subtraction between two Operand variables.
double Operand::operator- (Operand const& rhs) const {
    return Get() - rhs.Get();
}

// Overloading == operator for equality comparison between two Operand variables.
bool Operand::operator== (Operand const& rhs) const {
    return Get() == rhs.Get();
}

// Overloading > operator for greater than comparison between two Operand variables.
bool Operand::operator> (Operand const& rhs) const {
    return Get() > rhs.Get();
}

// Overloading < operator for less than comparison between two Operand variables.
bool Operand::operator< (Operand const& rhs) const {
    return Get() < rhs.Get();
}

// Mutator function to create a new entry to the unordered_map
// defined in Program.
double& Operand::Get () {
    return _program[VarName];
}

// Accessor function to fetch either a constant value or a value from
// Program's unordered_map dictionary.
double Operand::Get () const {
    return _isConst ? Const : static_cast<Program const&>(_program)[VarName];
}

// Overloaded >> operator to fetch input for an Operand obj.
std::istream& operator>> (std::istream& stream, Operand& obj) {
    return stream >> obj.Get();
}

// Overloading << operator to fetch content of an Operand obj.
std::ostream& operator<< (std::ostream& stream, Operand const& obj) {
    return stream << obj.Get();
}
