#pragma once
#include <iostream>
#include "FileReader.h"
#include "Lexer.h"
#include "Token.h"

using namespace std;


class Automaton 
{

protected:
    int inputRead = 0;
    int newLines = 0;
    Token::TokenType type;

    Automaton() 
    {

    }

public:
    Automaton(Token::TokenType type) 
    {
        this->type = type; 
    }

    virtual int Start(const string input) = 0;

    virtual Token* CreateToken(string input, int lineNo) 
    {
        return new Token(type, input, lineNo);
    }

    virtual int NewLinesRead() const 
    {
        return newLines;
    }
};
