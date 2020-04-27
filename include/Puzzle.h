#pragma once
#include <vector>
#include <string>
#include "../include/Cell.h"
using namespace std;

class Puzzle{
	public:
		Puzzle(string readFile);

	protected:
  	vector<vector<Cell*> > puzzle;
};
