#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
using namespace std;

class Token {

public:
	enum TokenType 
	{ 
		COMMA,
		PERIOD,
		Q_MARK,
		LEFT_PAREN,
		RIGHT_PAREN,
		COLON, 
		COLON_DASH,
		MULTIPLY,
		ADD,
		SCHEMES,
		FACTS,
		RULES,
		QUERIES,
		ID, 
		STRING, 
		COMMENT,
		UNDEFINED,
		END_OF_FILE
	};

	string TokenStrings[18] = {
		"COMMA",
		"PERIOD",
		"Q_MARK",
		"LEFT_PAREN",
		"RIGHT_PAREN",
		"COLON", 
		"COLON_DASH",
		"MULTIPLY",
		"ADD",
		"SCHEMES",
		"FACTS",
		"RULES",
		"QUERIES",
		"ID", 
		"STRING", 
		"COMMENT",
		"UNDEFINED",
		"EOF"
	};
	
	TokenType type;
	string value;
	int line;

	string toString() 
	{
		return ("(" + getType(type) + ",\"" + value + "\"," + to_string(line) + ")");
	}

	string getType(TokenType tokenType) 
	{
		return TokenStrings[tokenType];
	}
	
	Token(TokenType type, string value, int line) 
	{
		this->type = type;
		this->value = value;
		this->line = line;
	}

	Token() {}
};