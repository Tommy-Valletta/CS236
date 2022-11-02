#include "Automaton.h"
#include "Token.h"
#include <ctype.h>
#include "FactsAutomata.h"
#include "RulesAutomata.h"
#include "QueriesAutomata.h"
#include "SchemesAutomata.h"

class IdAutomata : public Automaton
{

public:
    IdAutomata() : Automaton()
    {
        this->type = Token::TokenType::ID;
    }

    int Start(const string input)
    {
        int inputSize = input.size();
        FactsAutomata *factsAutomata;
        RulesAutomata *rulesAutomata;
        QueriesAutomata *queriesAutomata;
        SchemesAutomata *schemesAutomata;

        if (isalpha(input[0]))
        {
            factsAutomata = new FactsAutomata();
            rulesAutomata = new RulesAutomata();
            queriesAutomata = new QueriesAutomata();
            schemesAutomata = new SchemesAutomata();
            if (factsAutomata->Start(input) > 0 || 
                rulesAutomata->Start(input) > 0 || 
                queriesAutomata->Start(input) > 0 || 
                schemesAutomata->Start(input) > 0) 
            {
                return 0;
            }

            int counter = 0;
            while (counter < inputSize && isalnum(input[counter])) {
                counter++;
            }

            return counter;
        }
        return 0;
    }
};
