#include <iostream>
#include <vector>
using namespace std;

//prototypes
vector<int> possible(int format, size_t r, size_t c, vector<vector<int> > *puzzle);

int main()
{
	vector<vector<int> > puzzle{{1},{2},{8},{6},{0},{0},{0},{3},{9}};
	vector<int> options;

	//row
	puzzle.at(0).push_back(3);
	puzzle.at(0).push_back(0);
	puzzle.at(0).push_back(0);
	puzzle.at(0).push_back(0);
	puzzle.at(0).push_back(5);
	puzzle.at(0).push_back(7);
	puzzle.at(0).push_back(8);
	puzzle.at(0).push_back(6);


/*
	//column
	puzzle.push_back(1);
	puzzle.push_back(2);
	puzzle.push_back(8);
	puzzle.push_back(6);
	puzzle.push_back(0);
	puzzle.push_back(0);
	puzzle.push_back(0);
	puzzle.push_back(3);
	puzzle.push_back(9);
*/


	options = possible(0, 0, 0, &puzzle);
	for(int c = 0; c < options.size(); c++)
		cout << options.at(c) << endl;
}

vector<int> possible(int format, size_t r, size_t c, vector<vector <int> > *puzzle){
	vector<int> options{9, 1, 2, 3, 4, 5, 6, 7, 8};
	int val = 0;

	if(format == 0){ //row
		for(c = 0; c < puzzle->at(0).size(); c++){
			//get value
			val = puzzle->at(r).at(c);

			//check if number
			if(val != 0){
				options.at(val % options.size()) = 0;
			}
		}

		return options;
	}
	else if(format == 1){ //col
		for(r = 0; r < puzzle->size(); r++){
			//get value
			val = puzzle->at(r).at(c);

			//check if number
			if(val != 0){
				options.at(val % options.size()) = 0;
			}

		}

		return options;
	}
	else if(format == 2){ //block

	}
	else{
		//bad
	}
}
