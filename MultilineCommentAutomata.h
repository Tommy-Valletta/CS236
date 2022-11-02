#include "Automaton.h"
#include "Token.h"
#include <ctype.h>

class MultilineCommentAutomata : public Automaton
{


protected:
    int FindTerminator(const string input, const int startPos) {
        int inputSize = input.size();
        int counter = startPos;
        bool keepGoing = true;
        while (counter < inputSize && keepGoing) {
            if (input[counter] == '#' && input[counter - 1] == '|') {
                keepGoing = false;
            }
            counter++;
        }
        return counter;
    }

public:
    MultilineCommentAutomata() : Automaton()
    {
        this->type = Token::TokenType::COMMENT;
    }

    int Start(const string input)
    {
        int inputSize = input.size();
        if (inputSize > 1 && input[0] == '#' && input[1] == '|')
        {
            int terminatorReturn = FindTerminator(input, 3);
            // cout << "Start terminatorReturn: " << terminatorReturn << endl; 
            return terminatorReturn;
        }
        return 0;
    }

    int Finish(const string input) {
        int terminatorReturn = FindTerminator(input, 0);
        // cout << "Finish terminatorReturn: " << terminatorReturn << endl; 
        return terminatorReturn;
    }
};
