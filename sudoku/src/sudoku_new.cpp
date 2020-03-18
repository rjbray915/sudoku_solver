#include <iostream>
#include <vector>
using namespace std;

//prototypes
vector<int> possible(size_t r, size_t c, vector<vector<int> > *puzzle);
void printOptions(vector<int> *options);
void assessBlock(int row, int col, vector<vector<int> > *puzzle);

int main()
{
	vector<vector<int> > puzzle{{7,0,0,1,0,0,0,3,8},
								{0,0,0,7,0,0,0,2,0},
								{0,2,4,0,0,0,0,0,9},
								{0,0,0,5,3,0,0,1,6},
								{0,0,0,0,7,0,0,0,0},
								{8,1,0,0,0,0,0,0,0},
								{9,8,0,0,0,4,2,0,0},
								{0,0,3,0,2,0,0,7,0},
								{0,0,0,0,0,0,0,0,0}};
	size_t i, j;
	
	size_t c = 0;
	while(c < 10000){
		for(i = 0; i < puzzle.size(); i += 3){
			for(j = 0; j < puzzle.at(0).size(); j += 3){
				assessBlock(i, j, &puzzle);
			}
		}

		c++;
	}

	for(size_t row = 0; row < puzzle.size(); row++){
			for(size_t col = 0; col < puzzle.at(0).size(); col++){
				cout << puzzle.at(row).at(col) << " ";
			}
			cout << "\n";
		}
	cout << "\n";
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

void assessBlock(int row, int col, vector<vector<int> > *puzzle){
	size_t i, j, k, countOption;
	vector<vector<int> > options, indexes;
	int chosenOpt;

	for(i = row; i < row+3; i++){
		for(j = col; j < col+3; j++){
			if(puzzle->at(i).at(j) == 0){
				options.push_back(possible(i, j, puzzle));
				indexes.push_back({i, j});
			}

		}
	}

	for(i = 0; i < options.size(); i++){
		
		//figure out if only one option is possible
		countOption = 0;
		for(j = 0; j < options.at(i).size(); j++){
			if(options.at(i).at(j) != 0){
				///*dlt*/cout << "only one " << options[i][j] << endl;
				chosenOpt = options.at(i).at(j);
				countOption++;
			}
		}

		if(countOption > 1){
			for(j = 0; j < options.at(0).size(); j++){

				if(options.at(i).at(j) != 0){
					k = i+1;
					countOption = 0;

					///*dlt*/ cout << "new option" << endl;

					while(k % options.size() != i){
						///*dlt*/cout << options.at(i).at(j) << " " << options.at(k%options.size()).at(j) << endl;

						if(options.at(k % options.size()).at(j) != 0){
							countOption++;
							break;
						}

						k++;
					}
				
					//no other has that option
					if(countOption == 0){
						///*dlt*/cout << "chosen" << options.at(i).at(j) << endl;
						size_t optionI = indexes.at(i).at(0);
						size_t optionJ = indexes.at(i).at(1);
						puzzle->at(optionI).at(optionJ) = options.at(i).at(j);
					}
				}
			}
		}
		else{
			///*dlt*/ cout << "one option\n";

			size_t optionI = indexes.at(i).at(0);
			size_t optionJ = indexes.at(i).at(1);
			puzzle->at(optionI).at(optionJ) = chosenOpt;
		}
	}

}

void printOptions(vector<int> *options){
	printf("{");
	for(size_t c = 0; c < options->size(); c++){
		printf("%2d,", options->at(c));
	}
	printf("}\n");
}
