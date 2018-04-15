#pragma once
#include "Problem.h"


class Algorithm {
public:
	Algorithm();
	~Algorithm();

	void backtracking(Problem problem);
	void forwardChecking(Problem problem);

	bool backtrack(Problem p, int rowStart, int colStart);
	bool forwardCheck(Problem p, int rowStart, int colStart);

	//helping functions
	bool isUnsignedLocation(Problem p);
	bool isAnyEmptyDomains(Problem p);


};

