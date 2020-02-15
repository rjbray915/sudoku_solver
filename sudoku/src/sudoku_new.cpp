#include <iostream>
#include <vector>
using namespace std;

//prototypes
vector<int> possible(size_t r, size_t c, vector<vector<int> > *puzzle);
void printOptions(vector<int> *options);

int main()
{
	vector<vector<int> > puzzle{{1,3,0,0,0,5,7,8,6},
		{2,0,0,0,0,4,0,0,5},
		{8,0,0,3,0,0,0,0,0},
		{6,8,0,0,0,0,5,0,0},
		{0,0,0,0,2,0,0,0,0},
		{0,0,7,0,0,0,0,9,1},
		{0,0,0,0,0,1,0,0,2},
		{3,0,0,4,0,0,0,0,8},
		{9,5,8,6,0,0,0,1,4}};
	vector<int> options;

	for(size_t row = 0; row < puzzle.size(); row++){
		for(size_t col = 0; col < puzzle.at(0).size(); col++){
			cout << puzzle.at(row).at(col) << endl;
			options = possible(row, col, &puzzle);
			printOptions(&options);
		}
	}
}

vector<int> possible(size_t r, size_t c, vector<vector <int> > *puzzle){
	vector<int> options{9, 1, 2, 3, 4, 5, 6, 7, 8};
	int val = 0;

	if(puzzle->at(r).at(c) != 0)
	{
		return {0,0,0,0,0,0,0,0,0};
	}

	//row
	for(size_t col = 0; col < puzzle->at(0).size(); col++){
		//get value
		val = puzzle->at(r).at(col);

		//check if number
		if(val != 0){
			options.at(val % options.size()) = 0;
		}
	}

	//col
	for(size_t row = 0; row < puzzle->size(); row++){
		//get value
		val = puzzle->at(row).at(c);

		//check if number
		if(val != 0){
			options.at(val % options.size()) = 0;
		}

	}

	//block
	size_t rowStart, colStart;
	rowStart = r/3 * 3;
	colStart = c/3 * 3;

	for(size_t row = rowStart; row < rowStart+3; row++){
		for(size_t col = colStart; col < colStart+3; col++){
			//get value
			val = puzzle->at(row).at(col);

			//check if number
			if(val != 0){
				options.at(val % options.size()) = 0;
			}
		}

	}



	return options;
}

void printOptions(vector<int> *options){
	printf("{");
	for(size_t c = 0; c < options->size(); c++){
		printf("%2d,", options->at(c));
	}
	printf("}\n");
}
