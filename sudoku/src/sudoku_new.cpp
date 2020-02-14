#include <iostream>
#include <vector>
using namespace std;

//prototypes
vector<int>* possible(int format, vector<int> *puzzle);

int main()
{

}

vector<int>* possible(int format, int r, int c = 0, vector<int> *puzzle){
	vector<int> options(9);
	
	if(format == 0){ //row
		for(c; c < options.size(); c++){
			options.at(puzzle.at(r).at(c))
		}
	}
	else if(format == 1){ //col

	}
	else if(format == 2){ //block

	}
	else{
		//bad
	}
}
