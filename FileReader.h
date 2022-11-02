#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

class FileReader 
{
public:
	char currentChar;
	int currentLine = 1;
	int charPointer;

	int getLineNumber() 
	{
		return currentLine;
	}

	char getNext() 
	{
		if (file->eof()) {
			return 0;
		}

		if (file->peek() == '\n') {
			currentLine++;
		}
		return file->get();
	}
	
	char peek() 
	{
		return file->peek();
	}
	
	ifstream* file;

	FileReader(string filename) 
	{
		file = new ifstream;
		file->open(filename);
		if (!*file) {
			cerr << "Unable to open file";
		}
	}
	
	~FileReader() 
	{
		file->close();
		delete file;
	}

};