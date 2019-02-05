#include "JH.h"

#include <string>

using namespace std;

int JH::stringToInt(string s)
{
	int i = atoi(s.c_str());

	return i;
}

string JH::intToString(int i)
{
	ostringstream strm;
	strm << i;

	return strm.str();
}