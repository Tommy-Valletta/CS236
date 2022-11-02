#pragma once
#include "Automaton.h"
#include "Token.h"

class FactsAutomata : public Automaton 
{

public:
    FactsAutomata() : Automaton()
    {
        this->type = Token::TokenType::FACTS; 
    }

    int Start(const string input) {
        string match = input.substr(0, 5);
        if (input.size() >= 5 && "Facts" == match) {
            if (input.size() >= 6 && isalpha(input[5])) {
                return 0;
            }
            return 5;
        }
        return 0;
    }
};
