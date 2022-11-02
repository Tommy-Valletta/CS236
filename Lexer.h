#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <ctype.h>
#include "Token.h"
#include "FileReader.h"
#include "CommaAutomata.h"
#include "UndefinedAutomata.h"
#include "PeriodAutomata.h"
#include "QmarkAutomata.h"
#include "LeftParenAutomata.h"
#include "RightParenAutomata.h"
#include "ColonDashAutomata.h"
#include "ColonAutomata.h"
#include "AddAutomata.h"
#include "MultiplyAutomata.h"
#include "SchemesAutomata.h"
#include "FactsAutomata.h"
#include "RulesAutomata.h"
#include "QueriesAutomata.h"
#include "IdAutomata.h"
#include "StringAutomata.h"
#include "CommentAutomata.h"
#include "MultilineCommentAutomata.h"
#include "MultilineStringAutomata.h"

using namespace std;

class Lexer {
    private:
        string content;
        vector<Token*> tokens;
        vector<Automaton*> automata;
        MultilineCommentAutomata* multilineCommentAutomata;
        MultilineStringAutomata* multilineStringAutomata;

    protected:
        void AddToken(string tokenStr, Automaton* maxAutomaton, int line) {
            Token *token = maxAutomaton->CreateToken(tokenStr, line);
            // DEBUG
            cout << token->toString() << endl;
            // DEBUG
            tokens.push_back(token);
        }

        void End(int line, int tokenCount) {
            Token *token = new Token(Token::TokenType::END_OF_FILE, "", line);
            cout << token->toString() << endl;
            tokens.push_back(token);
            cout << "Total Tokens = " << tokenCount << " ";
            exit(0);
        }

    public:
        Lexer(string content) {
            this->content = content;

            multilineCommentAutomata = new MultilineCommentAutomata();
            multilineStringAutomata = new MultilineStringAutomata();

            // Add all of the Automaton instances
            automata.push_back(new CommaAutomata());
            automata.push_back(new PeriodAutomata());
            automata.push_back(new QmarkAutomata());
            automata.push_back(new LeftParenAutomata());
            automata.push_back(new RightParenAutomata());
            automata.push_back(new ColonDashAutomata());
            automata.push_back(new ColonAutomata());
            automata.push_back(new AddAutomata());
            automata.push_back(new MultiplyAutomata());
            automata.push_back(new SchemesAutomata());
            automata.push_back(new FactsAutomata());
            automata.push_back(new RulesAutomata());
            automata.push_back(new QueriesAutomata());
            automata.push_back(new IdAutomata());
            automata.push_back(new CommentAutomata());
            automata.push_back(new UndefinedAutomata());
        }
        
        void Run() {
            vector<string> lines;
            int contentSize = content.size();
            // int automataSize = automata.size();

            int last = 0;
            for (int c = 0; c <= contentSize; c++)
            {
                if (content[c] == '\n' || c == contentSize) {
                    string line = content.substr(last, c - last);
                    lines.push_back(line);
                    last = c + 1;
                    // cout << line << endl;
                }
            }

            for (int l = 0; l < lines.size(); l++)
            {
                string line = lines[l];
                for (int p = 0; p < line.size(); p++)
                {
                    int maxRead = 0;
                    // int maxAutomaton = 0;
                    Automaton* maxAutomaton;

                    string rest = line.substr(p);
                    if (!rest.size() || isspace(rest.at(0))) continue;

                    // All this crap is for Multiline Comments
                    int multilineCommentMatch = multilineCommentAutomata->Start(rest);
                    // cout << "multilineCommentMatch: " << multilineCommentMatch << endl;
                    // cout << "rest[multilineCommentMatch]: " << rest[multilineCommentMatch] << endl;
                    // cout << "rest: " << rest << endl;
                    // cout << 999 << endl;
                    string multilineCommentStr;
                    if (multilineCommentMatch) {
                        int startLine = l;
                        try {
                            if (rest[multilineCommentMatch - 1] == '#' && rest[multilineCommentMatch - 2] == '|') {
                                maxRead = multilineCommentMatch;
                                maxAutomaton = multilineCommentAutomata;
                            } else {
                                multilineCommentStr = rest + '\n';
                                bool terminated = false;
                                bool moreOnLine = false;
                                int ll;
                                for (ll = l + 1; !terminated; ++ll) {
                                    string readAheadLine = lines.at(ll);
                                    int additionalChars = multilineCommentAutomata->Finish(readAheadLine);
                                    terminated = (readAheadLine[additionalChars - 1] == '#' &&  readAheadLine[additionalChars - 2] == '|');
                                    multilineCommentStr += terminated ? readAheadLine.substr(0, additionalChars) : readAheadLine + "\n";
                                    // cout << "readAheadLine: " << readAheadLine << endl;
                                    // cout << "additionalChars: " << additionalChars << endl;
                                    // cout << "readAheadLine.size(): " << readAheadLine.size() << endl;
                                    // cout << "should be #: " << readAheadLine[additionalChars - 1] << endl;
                                    // cout << "should be |: " << readAheadLine[additionalChars - 2] << endl;
                                    // cout << "terminated: " << terminated << endl;
                                    // cout << "multilineCommentStr: " << multilineCommentStr << endl;
                                    if (additionalChars < readAheadLine.size()) {
                                        rest = readAheadLine.substr(additionalChars);
                                        p = additionalChars;
                                        // cout << "additionalChars: " << additionalChars << endl;
                                        // cout << "rest: " << rest << endl;
                                        moreOnLine = true;
                                    }
                                }
                                if (terminated && moreOnLine) {
                                    l = ll - 1;
                                    line = lines[l];
                                } else {
                                    l = ll;
                                    line = rest = lines[l];
                                }
                                // cout << "moreOnLine?: " << moreOnLine << endl;
                                // cout << "p: " << p << endl;
                                // cout << "l: " << l << endl;
                                // cout << "rest: " << rest << endl;
                                AddToken(multilineCommentStr, new MultilineCommentAutomata(), startLine + 1);
                            }
                        } catch (const out_of_range& oor) {
                            // cout << "CATCH" << endl;
                            // cout << oor.what() << endl;
                            AddToken(multilineCommentStr, new UndefinedAutomata(), startLine + 1);
                            End(lines.size(), tokens.size() + 1);
                        }
                    } 

                    if (!rest.size() || isspace(rest.at(0))) continue;

                    // All this crap is for Multiline String
                    int multilineStringMatch = multilineStringAutomata->Start(rest);
                    // cout << " • multilineStringMatch: " << multilineStringMatch << endl;
                    // cout << " • rest[multilineStringMatch]: " << rest[multilineStringMatch] << endl;
                    // cout << " • rest: " << rest << endl;
                    // cout << 999 << endl;
                    string multilineStringStr;
                    if (multilineStringMatch) {
                        int startLine = l;
                        try {
                            if (multilineStringMatch > 1 && rest[multilineStringMatch - 1] == '\'') {
                                maxRead = multilineStringMatch;
                                maxAutomaton = multilineStringAutomata;
                                // cout << " • maxRead: " << maxRead << endl;
                            } else {
                                multilineStringStr = rest + '\n';
                                bool terminated = false;
                                bool moreOnLine = false;
                                int ll;
                                // cout << " • multilineStringStr: " << multilineStringStr << endl;
                                for (ll = l + 1; !terminated; ++ll) {
                                    string readAheadLine = lines.at(ll);
                                    int additionalChars = multilineStringAutomata->Finish(readAheadLine);
                                    // cout << "additionalChars: " << additionalChars << endl;
                                    if (additionalChars < 0) {
                                        additionalChars *= -1;
                                    } else {
                                        terminated = true;
                                    }
                                    // cout << "terminated: " << terminated << endl;
                                    multilineStringStr += terminated ? readAheadLine.substr(0, additionalChars) : readAheadLine + "\n";
                                    // cout << "multilineStringStr: " << multilineStringStr << endl;
                                    // cout << "readAheadLine: " << readAheadLine << endl;
                                    // cout << "additionalChars: " << additionalChars << endl;
                                    // cout << "readAheadLine.size(): " << readAheadLine.size() << endl;
                                    // cout << "should be #: " << readAheadLine[additionalChars - 1] << endl;
                                    // cout << "should be |: " << readAheadLine[additionalChars - 2] << endl;
                                    // cout << "terminated: " << terminated << endl;
                                    // cout << "multilineStringStr: " << multilineStringStr << endl;
                                    if (additionalChars < readAheadLine.size()) {
                                        rest = readAheadLine.substr(additionalChars);
                                        p = additionalChars;
                                        // cout << "additionalChars: " << additionalChars << endl;
                                        // cout << "rest: " << rest << endl;
                                        moreOnLine = true;
                                    }
                                }
                                // cout << "moreOnLine?: " << moreOnLine << endl;
                                // cout << "terminated?: " << terminated << endl;
                                if (terminated && moreOnLine) {
                                    l = ll - 1;
                                    line = lines[l];
                                } else {
                                    l = ll;
                                    line = rest = lines[l];
                                }
                                // cout << "moreOnLine?: " << moreOnLine << endl;
                                // cout << "p: " << p << endl;
                                // cout << "l: " << l << endl;
                                // cout << "rest: " << rest << endl;
                                // cout << " •• maxRead: " << maxRead << endl;
                                // cout << " •• rest.substr(0, maxRead): " << rest.substr(0, maxRead) << endl;
                                // cout << "tokens.size() " << tokens.size() << endl;
                                AddToken(multilineStringStr, new MultilineStringAutomata(), startLine + 1);
                                // cout << "tokens.size() " << tokens.size() << endl;
                            }
                        } catch (const out_of_range& oor) {
                            // cout << "CATCH" << endl;
                            // cout << oor.what() << endl;
                            AddToken(multilineStringStr, new UndefinedAutomata(), startLine + 1);
                            End(lines.size(), tokens.size() + 1);
                        }
                    } 

                    // here for ml strings that take the whole line
                    //   p = 0
                    //   l = next line
                    //   rest = whole line

                    // here for ml strings that split the last line
                    //   p = char after hashtag
                    //   l = same line
                    //   rest = substr(p)

                    if (!rest.size() || isspace(rest.at(0))) continue;

                    // This is for all the rest of the tokens
                    for (int a = 0; a < automata.size(); a++) 
                    {
                        Automaton* automaton = automata.at(a);
                        int inputRead = automaton->Start(rest);
                        if (inputRead > maxRead) {
                            maxRead = inputRead;
                            maxAutomaton = automaton;
                        }
                    }

                    // cout << " ••• maxRead: " << maxRead << endl;
                    // cout << " ••• rest.substr(0, maxRead): " << rest.substr(0, maxRead) << endl;
                    AddToken(rest.substr(0, maxRead), maxAutomaton, l + 1);
                    if (maxRead > 0) p += maxRead - 1;
                }
            }
            End(lines.size(), tokens.size() + 1);
        }
};
