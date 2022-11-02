#include "Automaton.h"
#include "Token.h"

class RightParenAutomata : public Automaton 
{

public:
    RightParenAutomata() : Automaton()
    {
        this->type = Token::TokenType::RIGHT_PAREN; 
    }

    int Start(const string input) {
        return input[0] == ')' ? 1 : 0;
    }
};
