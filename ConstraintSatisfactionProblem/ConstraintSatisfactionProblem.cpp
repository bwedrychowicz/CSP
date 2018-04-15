// ConstraintSatisfactionProblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Problem.h"
#include "Algorithm.h"

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

using namespace std;


int main(){	
	int n = 20; //number of repeat
	ofstream squareB("square4B.txt");

	
	//save times


	//create problems
	int latinSquareSize = 5;
	int graphSize = 10;

	int latinSquareDomainSize = latinSquareSize;
	int graphDomainSize = graphSize;

	Problem latinSquareProblem = Problem("square", latinSquareSize, latinSquareDomainSize);
	Problem graphProblem = Problem("graph", graphSize, graphDomainSize);
	//Problem sudokuPRoblem = Problem("sudoku", 9, 9);

	Algorithm alg = Algorithm();


	//alg.backtracking(latinSquareProblem);
	//cout << endl << endl;
	//latinSquareProblem.showProblem();

	/*alg.backtracking(graphProblem);
	cout << endl << endl;
	graphProblem.showProblem();*/

	//latinSquareProblem.showProblem();
	//latinSquareProblem.removeValueFromDomains(1, 1, 1);
	//cout << endl;
	//latinSquareProblem.problemBoard[1][1].domain.showDomain();

	alg.forwardChecking(latinSquareProblem);
	cout << endl << endl;
	latinSquareProblem.showProblem();

	//squareB << "latin square - 4x4<<endl";
	//for (int i = 0; i < n; i++) {
	//	Problem latinSquareProblem = Problem("square", latinSquareSize, latinSquareDomainSize);
	//	Algorithm alg = Algorithm();
	//	auto start = chrono::high_resolution_clock::now();
	//	alg.backtracking(latinSquareProblem);
	//	auto end = chrono::high_resolution_clock::now();
	//	auto dur = end - start;
	//	auto time = std::chrono::duration_cast<std::chrono::microseconds>(dur);
	//	//milisekundy
	//	squareB << (time.count()*0.001) <<endl;
	//}
	//squareB.close();



	system("PAUSE");
    return 0;
}

