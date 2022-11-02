#include "Automaton.h"
#include "Token.h"

class CommaAutomata : public Automaton 
{

public:
    CommaAutomata() : Automaton()
    {
        this->type = Token::TokenType::COMMA; 
    }

    int Start(const string input) {
        return input[0] == ',' ? 1 : 0;
    }
};
