#pragma once
#include "Automaton.h"
#include "Token.h"

class QueriesAutomata : public Automaton 
{

public:
    QueriesAutomata() : Automaton()
    {
        this->type = Token::TokenType::QUERIES; 
    }

    int Start(const string input) {
        string match = input.substr(0, 7);
        if (input.size() >= 7 && "Queries" == match) {
            if (input.size() >= 8 && isalpha(input[7])) {
                return 0;
            }
            return 7;
        }
        return 0;
    }
};
