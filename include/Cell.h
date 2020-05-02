#pragma once
#include <vector>
#include <cstdio>
using namespace std;

class Cell{
	public:
		Cell(int num, size_t row, size_t col);
		Cell& operator=(Cell& c);
		
		//cell utility
		void printOptions();
	protected:
		int num;
		size_t row, col;
		vector<int>* options;
		bool filled;
};
