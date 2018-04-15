#include "stdafx.h"
#include "Problem.h"


Problem::Problem() {
}

Problem::Problem(string pt, int ps, int domainSize) {
	setProblemSize(ps);
	setProblemType(pt);
	//create matrix
	problemBoard = new ProblemPart *[problemSize];

	for (int i = 0; i < problemSize; i++) {
		problemBoard[i] = new ProblemPart[problemSize];
	}

	//fill the matrix by zeros
	for (int i = 0; i < problemSize; i++) {
		for (int j = 0; j < problemSize; j++) {
			ProblemPart p = ProblemPart(Domain(domainSize), 0, i, j);
			problemBoard[i][j] = p;
		}
	}
}

Problem::~Problem() {
}



void Problem::setProblemSize(int size) {
	problemSize = size;
}

void Problem::setProblemType(string pt) {
	problemType = pt;
}

void Problem::updateProblem(int row, int col, int value) {
	problemBoard[row][col].value = value;
}

void Problem::showProblem() {
	for (int i = 0; i < problemSize; i++) {
		for (int j = 0; j < problemSize - 1; j++) {
			cout << problemBoard[i][j].value << ", ";
		}
		cout << problemBoard[i][problemSize - 1].value << endl;
	}
}



bool Problem::checkConstrains(int row, int col, int value) {
	//alowed types: square, graph, sudoku
	if (problemType == "square")
		return latinSquareConstraints(row, col, value);
	else if (problemType == "graph")
		return graphConstraints(row, col, value);
	else if (problemType == "sudoku")
		return sudokuConstraints(row, col, value);
	else
		return false;
}

bool Problem::latinSquareConstraints(int row, int col, int value) {
	bool satisfies = true;
	//row is the first dimension!!!
	if (numberExistInTheSameColumn(col, value) || numberExistInTheSameRow(row, value))
		satisfies = false;
	return satisfies;
}

bool Problem::graphConstraints(int row, int col, int value) {
	bool satisfies =true;
	if (!safeSide(row, col, value) || !safeCross(row, col, value))
		satisfies = false;
	return satisfies;
}

bool Problem::sudokuConstraints(int row, int col, int value) {
	bool satisfies = true;
	if (numberExistInTheSameColumn(col, value) || numberExistInTheSameRow(row, value) || !safeBox(row, col, value))
		satisfies = false;
	return satisfies;
}




bool Problem::numberExistInTheSameColumn(int column, int value) {
	bool exist = false;
	for (int i = 0; i < problemSize; i++) {
		if (problemBoard[i][column].value == value) {
			exist = true;
		}
	}
	return exist;
}

bool Problem::numberExistInTheSameRow(int row, int value) {
	bool exist = false;
	for (int i = 0; i < problemSize; i++) {
		if (problemBoard[row][i].value == value) {
			exist = true;
		}
	}
	return exist;
}

bool Problem::safeSide(int row, int column, int value) {
	bool satisfies = true;
	if ((row - 1) >= 0 && problemBoard[row - 1][column].value != 0 && abs(problemBoard[row - 1][column].value - value) < 2)
		satisfies = false;
	if ((row + 1)<problemSize && problemBoard[row + 1][column].value != 0 && abs(problemBoard[row + 1][column].value - value) < 2)
		satisfies = false;
	if ((column - 1) >= 0 && problemBoard[row][column - 1].value != 0 && abs(problemBoard[row][column - 1].value - value) < 2)
		satisfies = false;
	if ((column + 1)<problemSize && problemBoard[row][column + 1].value != 0 && abs(problemBoard[row][column + 1].value - value) < 2)
		satisfies = false;
	//false - nie mogê wpisaæ, true - mogê wpisaæ
	return satisfies;
}

bool Problem::safeCross(int row, int column, int value) {
	bool satisfies = true;

	if ((row - 2) >= 0 && problemBoard[row - 2][column].value!=0 && abs(problemBoard[row - 2][column].value - value) < 1)
		satisfies = false;
	if ((row + 2)<problemSize && problemBoard[row + 2][column].value != 0 && abs(problemBoard[row + 2][column].value - value) < 1)
		satisfies = false;
	if ((column - 2) >= 0 && problemBoard[row][column - 2].value != 0 && abs(problemBoard[row][column - 2].value - value) < 1)
		satisfies = false;
	if ((column + 2)<problemSize && problemBoard[row][column + 2].value != 0 && abs(problemBoard[row][column + 2].value - value) < 1)
		satisfies = false;

	if ((row - 1) >= 0 && (column - 1) >= 0 && problemBoard[row - 1][column - 1].value !=0 && abs(problemBoard[row - 1][column - 1].value - value) < 1)
		satisfies = false;
	if ((row + 1)<problemSize && (column - 1) >= 0 && problemBoard[row + 1][column - 1].value != 0 && abs(problemBoard[row + 1][column - 1].value - value) < 1)
		satisfies = false;
	if ((row - 1) >= 0 && (column + 1)<problemSize && problemBoard[row - 1][column + 1].value != 0 && abs(problemBoard[row - 1][column + 1].value - value) < 1)
		satisfies = false;
	if ((row + 1)<problemSize && (column + 1)<problemSize && problemBoard[row + 1][column + 1].value != 0 && abs(problemBoard[row + 1][column + 1].value - value) < 1)
		satisfies = false;

	//false - nie mogê wpisaæ, true - mogê wpisaæ
	return satisfies;
}

bool Problem::safeBox(int row, int column, int value) {
	bool satisfies = true;
	int rowStart;
	int colStart;

	if (column / 3 == 0)
		colStart = 0;
	else if (column / 3 == 1)
		colStart = 3;
	else if (column / 3 == 2)
		colStart = 6;

	if (row / 3 == 0)
		rowStart = 0;
	else if (row / 3 == 1)
		rowStart = 3;
	else if (row / 3 == 2)
		rowStart = 6;

	for (int i = rowStart; i < rowStart + 3; i++)
		for (int j = colStart; j < colStart + 3; j++)
			if (problemBoard[row][column].value == value)
				satisfies = false;

	return satisfies;
}



void Problem::removeValueFromDomains(int row, int col, int value) {
	//alowed types: square, graph, sudoku
	if (problemType == "square") {
		removeNumberInTheSameColumn(col, value);
		removeNumberInTheSameRow(row, value);
	} else if (problemType == "graph") {
		removeFromSide(row, col, value);
		removeFromCross(row, col, value);
	} 		
}

void Problem::fixDomains(int row, int col, int value) {
	//alowed types: square, graph, sudoku
	if (problemType == "square") {
		fixDomainInTheSameColumn(col, value);
		fixDomainInTheSameRow(row, value);
	} else if (problemType == "graph") {
		fixDomainFromSide(row, col, value);
		fixDomainCross(row, col, value);
	}

}

bool Problem::domainIsEmpty(int row, int col) {
	bool isEmpty = true;
	for (int i = 0; i < problemBoard[row][col].domain.domainSize; i++) {
		if (problemBoard[row][col].domain.domain[i] != 0)
			isEmpty = false;
	}
	return isEmpty;
}

int Problem::getNextDomainValue(int row, int col) {
	for (int i = 0; i < problemBoard[row][col].domain.domainSize; i++) {
		if (problemBoard[row][col].domain.domain[i] != 0)
			return i;
	}
	return -1;
}



void Problem::removeNumberInTheSameColumn(int column, int value) {
	for (int i = 0; i < problemSize; i++) {
		for (int j = 0; j < problemBoard[i][column].domain.domainSize; j++) {
			if (problemBoard[i][column].domain.domain[j] == value)
				problemBoard[i][column].domain.domain[j] = 0;
		}			
	}
}

void Problem::removeNumberInTheSameRow(int row, int value) {
	for (int i = 0; i < problemSize; i++) {
		for (int j = 0; j < problemBoard[row][i].domain.domainSize; j++) {
			if (problemBoard[row][i].domain.domain[j] == value)
				problemBoard[row][i].domain.domain[j] = 0;
		}
	}
}

void Problem::removeFromSide(int row, int column, int value) {
	if ((row - 1) >= 0) {
		for (int j = 0; j < problemBoard[row - 1][column].domain.domainSize; j++) {
			if (problemBoard[row - 1][column].domain.domain[j] == value)
				problemBoard[row - 1][column].domain.domain[j] = 0;
		}
	}
	if ((row + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row + 1][column].domain.domainSize; j++) {
			if (problemBoard[row + 1][column].domain.domain[j] == value)
				problemBoard[row + 1][column].domain.domain[j] = 0;
		}
	}
	if ((column - 1)>=0) {
		for (int j = 0; j < problemBoard[row][column - 1].domain.domainSize; j++) {
			if (problemBoard[row][column - 1].domain.domain[j] == value)
				problemBoard[row][column - 1].domain.domain[j] = 0;
		}
	}
	if ((column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row][column + 1].domain.domainSize; j++) {
			if (problemBoard[row][column + 1].domain.domain[j] == value)
				problemBoard[row][column + 1].domain.domain[j] = 0;
		}
	}
}

void Problem::removeFromCross(int row, int column, int value) {
	if ((row - 2) >= 0) {
		for (int j = 0; j < problemBoard[row - 2][column].domain.domainSize; j++) {
			if (problemBoard[row - 2][column].domain.domain[j] == value)
				problemBoard[row - 2][column].domain.domain[j] = 0;
		}
	}
	if ((row + 2) < problemSize) {
		for (int j = 0; j < problemBoard[row + 2][column].domain.domainSize; j++) {
			if (problemBoard[row + 2][column].domain.domain[j] == value)
				problemBoard[row + 2][column].domain.domain[j] = 0;
		}
	}
	if ((column - 2) >= 0) {
		for (int j = 0; j < problemBoard[row][column - 2].domain.domainSize; j++) {
			if (problemBoard[row][column - 2].domain.domain[j] == value)
				problemBoard[row][column - 2].domain.domain[j] = 0;
		}
	}
	if ((column + 2) < problemSize) {
		for (int j = 0; j < problemBoard[row][column + 2].domain.domainSize; j++) {
			if (problemBoard[row][column + 2].domain.domain[j] == value)
				problemBoard[row][column + 2].domain.domain[j] = 0;
		}
	}


	if ((row - 1) >= 0 && (column - 1) >= 0) {
		for (int j = 0; j < problemBoard[row - 1][column - 1].domain.domainSize; j++) {
			if (problemBoard[row - 1][column - 1].domain.domain[j] == value)
				problemBoard[row - 1][column - 1].domain.domain[j] = 0;
		}
	}
	if ((row + 1) < problemSize && (column - 1) >= 0) {
		for (int j = 0; j < problemBoard[row + 1][column - 1].domain.domainSize; j++) {
			if (problemBoard[row + 1][column - 1].domain.domain[j] == value)
				problemBoard[row + 1][column - 1].domain.domain[j] = 0;
		}
	}
	if ((row - 1) >= 0 && (column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row - 1][column + 1].domain.domainSize; j++) {
			if (problemBoard[row - 1][column + 1].domain.domain[j] == value)
				problemBoard[row - 1][column + 1].domain.domain[j] = 0;
		}
	}
	if ((row + 1) < problemSize && (column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row + 1][column + 1].domain.domainSize; j++) {
			if (problemBoard[row + 1][column + 1].domain.domain[j] == value)
				problemBoard[row + 1][column + 1].domain.domain[j] = 0;
		}
	}
}


void Problem::fixDomainInTheSameColumn(int column, int value) {
	//bool insert = false;
	for (int i = 0; i < problemSize; i++) {
	//	for (int j = 0; j < problemBoard[i][column].domain.domainSize; j++) {
	//		if (problemBoard[i][column].domain.domain[j] == 0 && insert == false) {
	//			problemBoard[i][column].domain.domain[j] = value;
	//			insert = true;
	//		}
	//	}
	//	insert = false;
		if (problemBoard[i][column].domain.domain[value - 1] == 0)
			problemBoard[i][column].domain.domain[value - 1] = value;
	}
}

void Problem::fixDomainInTheSameRow(int row, int value) {
	//bool insert = false;
	for (int i = 0; i < problemSize; i++) {
	//	for (int j = 0; j < problemBoard[row][i].domain.domainSize; j++) {
	//		if (problemBoard[row][i].domain.domain[j] == 0 && insert == false){
	//			problemBoard[row][i].domain.domain[j] = value;
	//			insert = true;
	//		}
	//	}
	//	insert = false;
		if (problemBoard[row][i].domain.domain[value - 1] == 0)
			problemBoard[row][i].domain.domain[value - 1] = value;
	}
}

void Problem::fixDomainFromSide(int row, int column, int value) {
	bool insert = false;
	if ((row - 1) >= 0) {
		for (int j = 0; j < problemBoard[row - 1][column].domain.domainSize; j++) {
			if (problemBoard[row - 1][column].domain.domain[j] == 0 && insert == false){
				problemBoard[row - 1][column].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((row + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row + 1][column].domain.domainSize; j++) {
			if (problemBoard[row + 1][column].domain.domain[j] == 0 && insert == false){
				problemBoard[row + 1][column].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((column - 1) >= 0) {
		for (int j = 0; j < problemBoard[row][column - 1].domain.domainSize; j++) {
			if (problemBoard[row][column - 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row][column - 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row][column + 1].domain.domainSize; j++) {
			if (problemBoard[row][column + 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row][column + 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
}

void Problem::fixDomainCross(int row, int column, int value) {
	bool insert = false;
	if ((row - 2) >= 0) {
		for (int j = 0; j < problemBoard[row - 2][column].domain.domainSize; j++) {
			if (problemBoard[row - 2][column].domain.domain[j] == 0 && insert == false){
				problemBoard[row - 2][column].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((row + 2) < problemSize) {
		for (int j = 0; j < problemBoard[row + 2][column].domain.domainSize; j++) {
			if (problemBoard[row + 2][column].domain.domain[j] == 0 && insert == false){
				problemBoard[row + 2][column].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((column - 2) >= 0) {
		for (int j = 0; j < problemBoard[row][column - 2].domain.domainSize; j++) {
			if (problemBoard[row][column - 2].domain.domain[j] == 0 && insert == false){
				problemBoard[row][column - 2].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((column + 2) < problemSize) {
		for (int j = 0; j < problemBoard[row][column + 2].domain.domainSize; j++) {
			if (problemBoard[row][column + 2].domain.domain[j] == 0 && insert == false){
				problemBoard[row][column + 2].domain.domain[j] = value;
				insert = true;
			}
		}
	}


	if ((row - 1) >= 0 && (column - 1) >= 0) {
		for (int j = 0; j < problemBoard[row - 1][column - 1].domain.domainSize; j++) {
			if (problemBoard[row - 1][column - 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row - 1][column - 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((row + 1) < problemSize && (column - 1) >= 0) {
		for (int j = 0; j < problemBoard[row + 1][column - 1].domain.domainSize; j++) {
			if (problemBoard[row + 1][column - 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row + 1][column - 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((row - 1) >= 0 && (column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row - 1][column + 1].domain.domainSize; j++) {
			if (problemBoard[row - 1][column + 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row - 1][column + 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
	if ((row + 1) < problemSize && (column + 1) < problemSize) {
		for (int j = 0; j < problemBoard[row + 1][column + 1].domain.domainSize; j++) {
			if (problemBoard[row + 1][column + 1].domain.domain[j] == 0 && insert == false){
				problemBoard[row + 1][column + 1].domain.domain[j] = value;
				insert = true;
			}
		}
	}
}