#include "Automaton.h"
#include "Token.h"

class ColonDashAutomata : public Automaton 
{

public:
    ColonDashAutomata() : Automaton()
    {
        this->type = Token::TokenType::COLON_DASH; 
    }

    int Start(const string input) {
        return input.size() > 1 && input[0] == ':' && input[1] == '-' ? 2 : 0;

        // if (input[0] == ':' && input[1] == '-') 
        // {
        //     return 2;
        // } else {
        //     return 0;
        // }
    }
};
