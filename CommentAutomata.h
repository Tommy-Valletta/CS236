#include "Automaton.h"
#include "Token.h"
#include <ctype.h>

class CommentAutomata : public Automaton
{

public:
    CommentAutomata() : Automaton()
    {
        this->type = Token::TokenType::COMMENT;
    }

    int Start(const string input)
    {
        int inputSize = input.size();
        if (input[0] == '#')
        {
            if (inputSize > 1 && input[1] == '|')
            {
                return 0;
            }
            return inputSize;
        }
        return 0;
    }
};
