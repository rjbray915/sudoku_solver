#pragma once
#include <vector>
#include <string>
#include "../include/Cell.h"
using namespace std;

class Puzzle{
	public:
		Puzzle(string readFile);
		Puzzle& operator=(Puzzle& p);

		//options
		void genOptions(size_t row, size_t col);
		
		//printing
		void printPuzzle();
		void printOptions();

		//setters

	protected:
  	vector<vector<Cell*> > puzzle;
};
