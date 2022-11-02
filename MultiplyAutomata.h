#include "Automaton.h"
#include "Token.h"

class MultiplyAutomata : public Automaton 
{

public:
    MultiplyAutomata() : Automaton()
    {
        this->type = Token::TokenType::MULTIPLY; 
    }

    int Start(const string input) {
        return input[0] == '*' ? 1 : 0;
    }
};
