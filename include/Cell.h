#pragma once
#include <vector>
using namespace std;

class Cell{
	public:
		Cell(int num, size_t row, size_t col);

	protected:
		int num;
		size_t row, col;
		vector<int> options;
};
