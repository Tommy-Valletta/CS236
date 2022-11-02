#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "FileReader.h"
#include "Lexer.h"
#include "Token.h"
//#include "Scanner.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Make dsure input is provided
	if (argc < 2 || *argv[1] == -1)
	{
		cerr << "No input file found." << endl;
		return 1;
	}

	// Token Test
	// cout << "--- token test ---" << endl;
	// Token::TokenType type = Token::COLON;
	// Token *t1 = new Token(type, ":", 6);
	// cout << t1->toString() << endl << endl;

	// FileReader Test
	// cout << "--- filereader test ---" << endl;
    // FileReader *reader = new FileReader(argv[1]);
	// char c = reader->getNext();
	// while (c != 0) 
	// {
    // 	cout << c;
	// 	c = reader->getNext();
	// };
	// cout << endl << endl;

	// File to String test
	// cout << "--- file to string test ---" << endl;
	ifstream file(argv[1]);
	stringstream buffer;
	buffer << file.rdbuf();
	// cout << buffer.str() << endl << endl;

	// Lexer test
	// cout << "--- lexer test ---" << endl;
	Lexer *lexer = new Lexer(buffer.str());
	lexer->Run();

    // cout << "DONE" << endl;
	return 0;
}