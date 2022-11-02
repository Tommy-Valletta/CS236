#include "Automaton.h"
#include "Token.h"

class ColonAutomata : public Automaton 
{

public:
    ColonAutomata() : Automaton()
    {
        this->type = Token::TokenType::COLON; 
    }

    int Start(const string input) {
        return input[0] == ':' ? 1 : 0;
    }
};
