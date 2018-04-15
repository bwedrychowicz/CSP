#pragma once
#include "Domain.h"

class ProblemPart {
public:

	Domain domain;
	int value;
	int row;
	int column;
	int domainPlace;

	ProblemPart();
	ProblemPart(Domain domain, int value, int row,	int column);
	~ProblemPart();
};

