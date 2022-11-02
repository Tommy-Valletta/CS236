#pragma once
#include "Automaton.h"
#include "Token.h"

class SchemesAutomata : public Automaton 
{

public:
    SchemesAutomata() : Automaton()
    {
        this->type = Token::TokenType::SCHEMES; 
    }

    int Start(const string input) {
        string match = input.substr(0, 7);
        if (input.size() >= 7 && "Schemes" == match) {
            if (input.size() >= 8 && isalpha(input[7])) {
                return 0;
            }
            return 7;
        }
        return 0;
    }
};
