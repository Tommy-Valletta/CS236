#include "Automaton.h"
#include "Token.h"

class QmarkAutomata : public Automaton 
{

public:
    QmarkAutomata() : Automaton()
    {
        this->type = Token::TokenType::Q_MARK; 
    }

    int Start(const string input) {
        return input[0] == '?' ? 1 : 0;
    }
};
