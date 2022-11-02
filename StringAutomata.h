#include "Automaton.h"
#include "Token.h"
#include <ctype.h>

class StringAutomata : public Automaton
{

public:
    StringAutomata() : Automaton()
    {
        this->type = Token::TokenType::STRING;
    }

    int Start(const string input)
    {
        int inputSize = input.size();
        if (input[0] == '\'')
        {
            int counter = 1;
            bool keepGoing = true;
            while (counter < inputSize && keepGoing) {
                if (input[counter] == '\'') {
                    if (inputSize >= counter + 1 && input[counter + 1] == '\'') {
                        counter ++;
                    } else {
                        keepGoing = false;
                    }
                }
                counter++;
            }
            return input[counter - 1] == '\'' ? counter : 0;
        }
        return 0;
    }
};
