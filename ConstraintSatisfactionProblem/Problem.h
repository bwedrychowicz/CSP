#pragma once
#include "ProblemPart.h"
#include "Domain.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Problem {
public:

	ProblemPart **problemBoard;
	int problemSize;
	string problemType; //allowed type: square, graph, sudoku

	Problem();
	Problem(string problemType, int problemSize, int domainSize);
	~Problem();

	void setProblemSize(int size);
	void setProblemType(string problemType);
	void updateProblem(int row, int col, int value);

	void showProblem();
	void saveToFile(string fileName, string matrixName);

	//constraints
	bool checkConstrains(int row, int col, int value);
	bool latinSquareConstraints(int row, int col, int value);
	bool graphConstraints(int row, int col, int value);
	bool sudokuConstraints(int row, int col, int value);


	//help for constraints
	bool numberExistInTheSameColumn(int column, int value);
	bool numberExistInTheSameRow(int row, int value);
	bool safeSide(int row, int column, int value);
	bool safeCross(int row, int column, int value);
	bool safeBox(int row, int column, int value);

	//manipulate by domains
	void removeValueFromDomains(int row, int col, int value);
	void fixDomains(int row, int col, int value);
	bool domainIsEmpty(int row, int col);
	int getNextDomainValue(int row, int col);

	//help for forward checking
	void removeNumberInTheSameColumn(int column, int value);
	void removeNumberInTheSameRow(int row, int value);
	void removeFromSide(int row, int column, int value);
	void removeFromCross(int row, int column, int value);
	void fixDomainInTheSameColumn(int column, int value);
	void fixDomainInTheSameRow(int row, int value);
	void fixDomainFromSide(int row, int column, int value);
	void fixDomainCross(int row, int column, int value);
};

