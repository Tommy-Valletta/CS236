#include "Automaton.h"
#include "Token.h"

class UndefinedAutomata : public Automaton 
{

public:
    UndefinedAutomata() : Automaton()
    {
        this->type = Token::TokenType::UNDEFINED; 
    }

    int Start(const string input) {
        return 1;
    }
};
