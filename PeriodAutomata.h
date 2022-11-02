#include "Automaton.h"
#include "Token.h"

class PeriodAutomata : public Automaton 
{

public:
   PeriodAutomata() : Automaton()
    {
        this->type = Token::TokenType::PERIOD; 
    }

    int Start(const string input) {
        return input[0] == '.' ? 1 : 0;
    }
};
