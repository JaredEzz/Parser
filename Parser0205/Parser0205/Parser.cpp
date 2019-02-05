#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Fact.h"
#include "Parser.h"
#include "Predicate.h"
#include "Query.h"
#include "Rule.h"
#include "Scanner.h"

using namespace std;

Token myToken("", 0, COMMA);
vector<Predicate> mySchemes;
vector<Predicate> myFacts;
vector<Rule> myRules;
vector<Predicate> myQueries;
set <string> domain;
set <string>::iterator it;

Parser::Parser()
{
	myIndex = 0;
}

void Parser::parse(vector<Token>& toParse)
{
	fillmyToken(toParse);
	match(SCHEMES);

	fillmyToken(toParse);
	match(COLON);
	parseSchemeList(toParse);

	match(FACTS);

	fillmyToken(toParse);
	match(COLON);
	fillmyToken(toParse);
	parseFactList(toParse);

	match(RULES);

	fillmyToken(toParse);
	match(COLON);
	fillmyToken(toParse);
	parseRuleList(toParse);

	match(QUERIES);

	fillmyToken(toParse);
	match(COLON);
	parseQueryList(toParse);
}

void Parser::match(tokenType t)
{
	if (t == myToken.getType())
	{
		advanceIndex();
	}
	else
	{
		throw(myToken);
	}
}

void Parser::advanceIndex()
{
	myIndex++;
}

void Parser::fillmyToken(vector<Token>& toParse)
{
	if ((size_t)myIndex < toParse.size())
	{
		myToken.data = toParse.at(myIndex).getData();
		myToken.lineNum = toParse.at(myIndex).getLine();
		myToken.myType = toParse.at(myIndex).getType();
	}
	else
	{
		throw(myToken);
	}
}

void Parser::parseSchemeList(vector<Token>& toParse)
{
	while(myToken.myType != FACTS)
	{
		fillmyToken(toParse);
		match(ID);
		Predicate pred(myToken.data);

		fillmyToken(toParse);
		match(LEFT_PAREN);

		parseParamList(toParse, pred);

		match(RIGHT_PAREN);
		mySchemes.push_back(pred);

		fillmyToken(toParse);
	}
}

void Parser::parseParamList(vector<Token>& toParse, Predicate& p)
{
	fillmyToken(toParse);
	if(myToken.myType == STRING)
	{
		match(STRING);
		Parameter param(myToken.data, myToken.myType);
		p.addParameter(param);
		domain.insert(myToken.data);
	}
	else
	{
		match(ID);
		Parameter param(myToken.data, myToken.myType);
		p.addParameter(param);
	}

	fillmyToken(toParse);
	if(myToken.myType == COMMA)	//more parameters to read
	{
		advanceIndex();
		parseParamList(toParse, p);
	}
	else
	{
		//do nothing; no more parameters
	}

}

void Parser::parseFactList(vector<Token>& toParse)
{
	while(myToken.myType != RULES)
	{
		match(ID);
		Predicate pred(myToken.data);

		fillmyToken(toParse);
		match(LEFT_PAREN);

		parseParamList(toParse, pred);

		match(RIGHT_PAREN);

		fillmyToken(toParse);
		match(PERIOD);

		myFacts.push_back(pred);

		fillmyToken(toParse);
	}

}

void Parser::parseRuleList(vector<Token>& toParse)
{
	while(myToken.myType != QUERIES)
	{
		match(ID);
		Predicate pred(myToken.data);

		fillmyToken(toParse);
		match(LEFT_PAREN);

		parseParamList(toParse, pred);

		match(RIGHT_PAREN);

		Rule r(pred);

		fillmyToken(toParse);
		match(COLON_DASH);

		parsePredicateList(toParse, r);

		match(PERIOD);

		myRules.push_back(r);

		fillmyToken(toParse);
	}
}

void Parser::parseQueryList(vector<Token>& toParse)
{
	while((size_t) myIndex < toParse.size())
	{
		fillmyToken(toParse);
		match(ID);
		Predicate pred(myToken.data);

		fillmyToken(toParse);
		match(LEFT_PAREN);

		parseParamList(toParse, pred);

		match(RIGHT_PAREN);
		myQueries.push_back(pred);

		fillmyToken(toParse);
		match(Q_MARK);

		if((size_t) myIndex < toParse.size())
		{
			fillmyToken(toParse);
		}
	}
}

void Parser::parsePredicateList(vector<Token>& toParse, Rule& r)
{
	fillmyToken(toParse);
	match(ID);
	Predicate pred(myToken.data);

	fillmyToken(toParse);
	match(LEFT_PAREN);

	parseParamList(toParse, pred);

	r.addPredicate(pred);

	fillmyToken(toParse);
	match(RIGHT_PAREN);

	fillmyToken(toParse);
	if(myToken.myType == COMMA)	//another predicate list to read
	{
		advanceIndex();
		parsePredicateList(toParse, r);
	}
	else
	{
		//do nothing; not another predicate list
	}

}

void Parser::print(ofstream& out)
{

	 //cout << "Success!" << endl;
	out << "Success!" << endl;
	printSchemes(out);
	printFacts(out);
	printRules(out);
	printQueries(out);
	printDomain(out);
}

void Parser::printSchemes(ofstream& out)
{
	 //cout << "Schemes(" << mySchemes.size() << "):" << endl;
	out << "Schemes(" << mySchemes.size() << "):" << endl;

	for(size_t i = 0; i < mySchemes.size(); i++)
	{
		 //cout << mySchemes.at(i).toString();
		out << mySchemes.at(i).toString();

		for(size_t j = 0; j < mySchemes.at(i).paramList.size(); j++)
		{
			 //cout << mySchemes.at(i).paramList.at(j).toString();
			out << mySchemes.at(i).paramList.at(j).toString();

			if(j < (mySchemes.at(i).paramList.size() - 1))
			{
				 //cout << ",";
				out << ",";
			}
		}

		 //cout << ")" << endl;
		out << ")" << endl;
	}
}

void Parser::printFacts(ofstream& out)
{
	 //cout << "Facts(" << myFacts.size() << "):" << endl;
	out << "Facts(" << myFacts.size() << "):" << endl;

	for(size_t i = 0; i < myFacts.size(); i++)
	{
		 //cout << myFacts.at(i).toString();
		out << myFacts.at(i).toString();

		for(size_t j = 0; j < myFacts.at(i).paramList.size(); j++)
		{
			 //cout << myFacts.at(i).paramList.at(j).toString();
			out << myFacts.at(i).paramList.at(j).toString();

			if(j < (myFacts.at(i).paramList.size() - 1))
			{
				 //cout << ",";
				out << ",";
			}
		}
		 //cout << ")." << endl;
		out << ")." << endl;
	}
}

void Parser::printRules(ofstream& out)
{
	 //cout << "Rules(" << myRules.size() << "):" << endl;
	out << "Rules(" << myRules.size() << "):" << endl;
	for(size_t i = 0; i < myRules.size(); i++)
	{
		 //cout << "  " << myRules.at(i).myPred.info << "(";
		out << "  " << myRules.at(i).myPred.info << "(";

		for(size_t j = 0; j < myRules.at(i).myPred.paramList.size(); j++)
		{
			 //cout << myRules.at(i).myPred.paramList.at(j).toString();
			out << myRules.at(i).myPred.paramList.at(j).toString();
			if(j < (myRules.at(i).myPred.paramList.size()-1))
			{
				 //cout << ",";
				out << ",";
			}
		}
		 //cout << ") :- ";
		out << ") :- ";

		for(size_t k = 0; k < myRules.at(i).predList.size(); k++)
		{
			 //cout << myRules.at(i).predList.at(k).info << "(";
			out << myRules.at(i).predList.at(k).info << "(";

			for(size_t z = 0; z < myRules.at(i).predList.at(k).paramList.size(); z++)
			{
				 //cout << myRules.at(i).predList.at(k).paramList.at(z).toString();
				out << myRules.at(i).predList.at(k).paramList.at(z).toString();
				if(z < (myRules.at(i).predList.at(k).paramList.size() -1))
				{
					 //cout << ",";
					out << ",";
				}
			}
			if(k < (myRules.at(i).predList.size() - 1))
			{
				 //cout << "),";
				out << "),";
			}
			else
			{
				 //cout << ")." << endl;
				out << ")." << endl;
			}
		}
	}
}

void Parser::printQueries(ofstream& out)
{
	 //cout << "Queries(" << myQueries.size() << "):" << endl;
	out << "Queries(" << myQueries.size() << "):" << endl;

	for(size_t i = 0; i < myQueries.size(); i++)
	{
		 //cout << myQueries.at(i).toString();
		out << myQueries.at(i).toString();

		for(size_t j = 0; j < myQueries.at(i).paramList.size(); j++)
		{
			 //cout << myQueries.at(i).paramList.at(j).toString();
			out << myQueries.at(i).paramList.at(j).toString();

			if(j < (myQueries.at(i).paramList.size() - 1))
			{
				 //cout << ",";
				out << ",";
			}
		}

		 //cout << ")?" << endl;
		out << ")?" << endl;
	}
}

void Parser::printDomain(ofstream& out)
{
	  //cout << "Domain(" << domain.size() << "):" << endl;
	 out << "Domain(" << domain.size() << "):" << endl;

	  for (it = domain.begin(); it != domain.end(); it++)
	  {
		  //cout << "  \'" << *it << "\'" << endl;
		 out << "  \'" << *it << "\'" << endl;
	  }
}