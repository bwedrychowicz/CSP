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
	ofstream file("squareBacktrackingTime.txt");
	ofstream file2("squareForwardCheckingTime.txt");
	ofstream file3("graphBacktrackingTime.txt");
	ofstream file4("graphForwardCheckingTime.txt");
	ofstream file5("squareMatrix.txt");
	ofstream file6("graphMatrix.txt");

	

	Algorithm alg = Algorithm();

	//int latinSquareSize = 9;
	//int latinSquareDomainSize = latinSquareSize;
	//Problem latinSquareProblem = Problem("square", latinSquareSize, latinSquareDomainSize);
	//alg.backtracking(latinSquareProblem);
	//cout << endl << endl;
	//latinSquareProblem.showProblem();


	//int graphSize = 8;
	//int graphDomainSize = graphSize;
	//Problem graphProblem = Problem("graph", graphSize, graphDomainSize);
	//alg.backtracking(graphProblem);
	//cout << endl << endl;
	//graphProblem.showProblem();


	//alg.forwardChecking(graphProblem);
	//cout << endl << endl;
	//graphProblem.showProblem();




	//latin square - backtracking
	for (int latinSquareSize = 3; latinSquareSize < 10; latinSquareSize++) {
		int latinSquareDomainSize = latinSquareSize;
		double avg = 0;

		for (int i = 0; i < n; i++) {
			Problem latinSquareProblem = Problem("square", latinSquareSize, latinSquareDomainSize);
			Algorithm alg = Algorithm();
			auto start = chrono::high_resolution_clock::now();
			alg.backtracking(latinSquareProblem);
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - start;
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(dur);
			//milisekundy
			avg = avg + time.count()*0.001;
			//file << (time.count()*0.001) <<endl;
			//latinSquareProblem.saveToFile("squareMatrixB.txt", "matrixSquareB");
		}
		avg = avg / n;
		file << latinSquareSize << "\t" << avg << endl;
	}	
	file.close();


	//latin square forward checking
	for (int latinSquareSize = 3; latinSquareSize < 10; latinSquareSize++) {
		int latinSquareDomainSize = latinSquareSize;
		double avg = 0;

		for (int i = 0; i < n; i++) {
			Problem latinSquareProblem = Problem("square", latinSquareSize, latinSquareDomainSize);
			Algorithm alg = Algorithm();
			auto start = chrono::high_resolution_clock::now();
			alg.forwardChecking(latinSquareProblem);
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - start;
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(dur);
			//milisekundy
			avg = avg + time.count()*0.001;
			//latinSquareProblem.saveToFile("squareMatrixF.txt", "matrixSquareF");
		}
		avg = avg / n;
		file2 << latinSquareSize << "\t" << avg << endl;
	}
	file2.close();


	//graph backtracking
	for (int graphSize = 8; graphSize < 16; graphSize++) {
	int graphDomainSize = graphSize;
		double avg = 0;

		for (int i = 0; i < n; i++) {
			Problem graphProblem = Problem("graph", graphSize, graphDomainSize);
			Algorithm alg = Algorithm();
			auto start = chrono::high_resolution_clock::now();
			alg.backtracking(graphProblem);
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - start;
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(dur);
			//milisekundy
			avg = avg + time.count()*0.001;
			//graphProblem.saveToFile("graphB.txt", "matrixGraphB");
		}
		avg = avg / n;
		file3 << graphSize << "\t" << avg << endl;		
	}
	file3.close();


	//graph forward checking
	for (int graphSize = 8; graphSize < 16; graphSize++) {
		int graphDomainSize = graphSize;
		double avg = 0;

		for (int i = 0; i < n; i++) {
			Problem graphProblem = Problem("graph", graphSize, graphDomainSize);
			Algorithm alg = Algorithm();
			auto start = chrono::high_resolution_clock::now();
			alg.forwardChecking(graphProblem);
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - start;
			auto time = std::chrono::duration_cast<std::chrono::microseconds>(dur);
			//milisekundy
			avg = avg + time.count()*0.001;
			//graphProblem.saveToFile("graphF.txt", "matrixGraphF");
		}
		avg = avg / n;
		file4 << graphSize << "\t" << avg << endl;
	}
	file4.close();

	system("PAUSE");
    return 0;
}

