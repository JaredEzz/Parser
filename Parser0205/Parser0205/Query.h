#ifndef QUERY_H
#define QUERY_H

#include "Predicate.h"

using namespace std;

class Query {
	public:
		Predicate myPred;

		Query(Predicate);
};

#endif
