#include "Automaton.h"
#include "Token.h"

class LeftParenAutomata : public Automaton 
{

public:
    LeftParenAutomata() : Automaton()
    {
        this->type = Token::TokenType::LEFT_PAREN; 
    }

    int Start(const string input) {
        return input[0] == '(' ? 1 : 0;
    }
};
