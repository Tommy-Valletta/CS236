#include "Automaton.h"
#include "Token.h"
#include <ctype.h>

class MultilineStringAutomata : public Automaton
{

protected:
    int FindTerminator(const string input, const int startPos) {
        int inputSize = input.size();
        int counter = startPos;
        bool keepGoing = true;
        while (counter < inputSize && keepGoing) {
            if (input[counter] == '\'') {
                if (counter + 1 < inputSize && input[counter + 1] == '\'') {
                    counter++;
                } else {
                    keepGoing = false;
                }
            }
            counter++;
        }
        // cout << " • FindTerminator keepGoing: " << keepGoing << endl; 
        return keepGoing ? counter *= -1 : counter;
    }

public:
    MultilineStringAutomata() : Automaton()
    {
        this->type = Token::TokenType::STRING;
    }

    int Start(const string input)
    {
        int inputSize = input.size();
        if (inputSize >= 1 && input[0] == '\'')
        {
            int terminatorReturn = FindTerminator(input, 1);
            // cout << " • Start terminatorReturn: " << terminatorReturn << endl; 
            return terminatorReturn;
        }
        return 0;
    }

    int Finish(const string input) {
        int terminatorReturn = FindTerminator(input, 0);
        // cout << " • Finish terminatorReturn: " << terminatorReturn << endl; 
        return terminatorReturn;
    }
};
