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
		int searchOption(int num);

		//getters
		int getNum();
		bool isEmpty();

		//setters
		void setOptions(vector<int>* options);
	protected:
		int num;
		size_t row, col;
		vector<int>* options;
		bool empty;
};
