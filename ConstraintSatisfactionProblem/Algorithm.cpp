#include "stdafx.h"
#include "Algorithm.h"


Algorithm::Algorithm() {
}

Algorithm::~Algorithm() {
}

void Algorithm::backtracking(Problem problem) {
	backtrack(problem, 0, 0);
	//if (isUnsignedLocation(problem))
	//	cout << "nie rozwiazano";
	//else
	//	cout<<"rozwiazano";
}

void Algorithm::forwardChecking(Problem problem) {
	forwardCheck(problem, 0, 0);
	//if (isUnsignedLocation(problem))
	//	cout << "nie rozwiazano";
	//else
	//	cout << "rozwiazano";
}


bool Algorithm::backtrack(Problem p, int row, int col) {
	bool satisfy = false;
	int d = p.problemBoard[row][col].domainPlace;
	int domainSize = p.problemBoard[row][col].domain.domainSize;
	while (satisfy == false && d < domainSize) {
		if (p.checkConstrains(row, col, p.problemBoard[row][col].domain.domain[d])) {
			p.problemBoard[row][col].value = p.problemBoard[row][col].domain.domain[d];
			p.problemBoard[row][col].domainPlace = d + 1;
			satisfy = true;
			//cout << p.problemBoard[row][col].value << " ";
		}
		d++;
	}
	if (satisfy == true) {
		if (col + 1 == p.problemSize && row + 1 < p.problemSize) {
			//cout << endl;
			backtrack(p, row + 1, 0);
		} else if (col + 1 < p.problemSize && row < p.problemSize) {
			backtrack(p, row, col + 1);
		} else if (col + 1 == p.problemSize && row + 1 == p.problemSize)
			return true;
	} else {
		if (col - 1 < 0 && row - 1 < 0)
			return false;
		else if (col - 1 >= 0 && row >= 0) {
			//cout << "nawrot ";
			p.problemBoard[row][col].value = 0;
			p.problemBoard[row][col].domainPlace=0;
			backtrack(p, row, col - 1);
		}
		else if (col - 1 < 0 && row - 1 >= 0) {
			//cout << "nawrot ";
			p.problemBoard[row][col].value = 0;
			p.problemBoard[row][col].domainPlace=0;
			backtrack(p, row - 1, p.problemSize - 1);
		}
	}
	//return true;
}

  bool Algorithm::forwardCheck(Problem p, int row, int col) {
	int value=0;
	bool satisfy = false;
	int d = p.problemBoard[row][col].domainPlace;
	int domainSize = p.problemBoard[row][col].domain.domainSize;
	while (satisfy == false && d < domainSize) {

		int x = p.problemBoard[row][col].domain.domain[d];
		bool y = p.checkConstrains(row, col, p.problemBoard[row][col].domain.domain[d]);

		if (p.problemBoard[row][col].domain.domain[d] != 0 && p.checkConstrains(row, col, p.problemBoard[row][col].domain.domain[d])) {
			value = p.problemBoard[row][col].domain.domain[d];
			p.removeValueFromDomains(row, col, p.problemBoard[row][col].domain.domain[d]);
			p.problemBoard[row][col].value = value;
			if (!isAnyEmptyDomains(p)) {
				
				p.problemBoard[row][col].domainPlace = d + 1;
				satisfy = true;
				//cout << p.problemBoard[row][col].value << " ";
			} else {
				p.problemBoard[row][col].value = 0;
				p.fixDomains(row, col, value);
			}			
		}
		d++;
	}
	//d--;

	if (satisfy == true) {
		if (col + 1 == p.problemSize && row + 1 < p.problemSize) {
			//cout << endl;
			forwardCheck(p, row + 1, 0);
		} else if (col + 1 < p.problemSize && row < p.problemSize) {
			forwardCheck(p, row, col + 1);
		} else if (col + 1 == p.problemSize && row + 1 == p.problemSize)
			return true;
	} else {
		if (col - 1 < 0 && row - 1 < 0)
			return false;
		else if (col - 1 >= 0 && row >= 0) {
			//cout << "nawrot "<<endl<< p.problemBoard[row][col].domain.domain[d]<<endl;
			p.fixDomains(row, col-1, p.problemBoard[row][col-1].value);
			p.problemBoard[row][col].value = 0;
			p.problemBoard[row][col].domainPlace = 0;			
			forwardCheck(p, row, col - 1);
		} else if (col - 1 < 0 && row - 1 >= 0) {
			//cout << "nawrot ";
			p.fixDomains(row-1, p.problemSize - 1, p.problemBoard[row-1][p.problemSize - 1].value);
			p.problemBoard[row][col].value = 0;
			p.problemBoard[row][col].domainPlace = 0;
			forwardCheck(p, row - 1, p.problemSize - 1);
		}
	}
}


//help functions
bool Algorithm::isUnsignedLocation(Problem p) {
	for (int i = 0; i < p.problemSize; i++)
		for (int j = 0; j < p.problemSize; j++)
			if (p.problemBoard[i][j].value == 0 || p.problemBoard[i][j].value == 0)
				return true;
	return false;
}

bool Algorithm::isAnyEmptyDomains(Problem p) {
	for (int i = 0; i < p.problemSize; i++)
		for (int j = 0; j < p.problemSize; j++)
			if (p.problemBoard[i][j].value==0 && p.domainIsEmpty(i,j))
				return true;
	return false;
}

