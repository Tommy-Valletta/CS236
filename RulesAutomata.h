#pragma once
#include "Automaton.h"
#include "Token.h"

class RulesAutomata : public Automaton 
{

public:
    RulesAutomata() : Automaton()
    {
        this->type = Token::TokenType::RULES; 
    }

    int Start(const string input) {
        string match = input.substr(0, 5);
        if (input.size() >= 5 && "Rules" == match) {
            if (input.size() >= 6 && isalpha(input[5])) {
                return 0;
            }
            return 5;
        }
        return 0;
    }
};
