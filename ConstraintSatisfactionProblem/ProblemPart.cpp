#include "stdafx.h"
#include "ProblemPart.h"


ProblemPart::ProblemPart() {
}

ProblemPart::ProblemPart(Domain d, int v, int r, int c) {
	domain = d;
	value = v;
	row = r;
	column = c;
	domainPlace = 0;
}


ProblemPart::~ProblemPart() {
}
