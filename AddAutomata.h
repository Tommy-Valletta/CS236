#include "Automaton.h"
#include "Token.h"

class AddAutomata : public Automaton 
{

public:
    AddAutomata() : Automaton()
    {
        this->type = Token::TokenType::ADD; 
    }

    int Start(const string input) {
        return input[0] == '+' ? 1 : 0;
    }
};
