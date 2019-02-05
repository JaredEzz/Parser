#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"

#include <vector>

using namespace std;

class Scanner {
private:
	vector<Token> tokenDatabase;
	string data;
	string type;
	int line;
	bool error;
	int errorLineNumber;

	public:
		void scan(ifstream &);

		string typeToString(int);
		vector<Token>& getTokens();

		void comment(ifstream&);
		void logPunctuation(string);
		void print(ofstream&);

		bool checkForPunctuationInisID(char);

		bool isPunctuation(string, ifstream&);
		bool isACommaPeriodQuestionParen(string);
		void isString(string, ifstream&);
		void isColon(string, ifstream&);
		void isID(char, ifstream&);
		bool isQuoteColon(char, string, string, ifstream&);
		void isSpecial(string);

		bool stringIsSpace(string); // Ghetto "replacement" for the default isspace() function that accepts a string instead of a character

		void logError();
		void printError(int, ofstream&);
};

#endif
