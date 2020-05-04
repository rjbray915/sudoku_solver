#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../include/Puzzle.h"
using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	edit notes:
 * needs to add reading from fstream

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Puzzle::Puzzle(string readFile){
	int num;
	int count = 0;
	ifstream iFS( readFile );

	if( !iFS.is_open() ){
		throw( (string)"could not open file\n" );
	}	
	//set number of rows
	puzzle.resize(9);

	while(iFS >> num){
		//c/9 gives row b/c groupings of 9, c%9 gives displacement
		if(num < 0 || num > 9){
			throw ( (string)"bad read file\n" );
		}

		puzzle.at(count%9).push_back( new Cell(num, count/9, count%9) );
		count++;
	}

	if(count != 81){
		throw( (string)"bad read file\n");
	}
}

Puzzle& Puzzle::operator=(Puzzle& p){
	size_t i, j;

	//deallocating vector cells
	for(i = 0; i < puzzle.size(); i++){
		for(j = 0; j < puzzle.at(i).size(); j++){
			delete puzzle.at(i).at(j);
		}
	}

	puzzle = p.puzzle;

	return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	options
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Puzzle::genOptions(size_t row, size_t col){
	vector<int>* options = new vector<int>; 
	int val = 0;
	size_t i;

	if(puzzle.at(row).at(col)->getNum() != 0)
	{   
		puzzle.at(row).at(col)->setOptions(options);
	}

	options->resize(9);
	for(i = 1; i <= 9; i++){
		options->at(i % options->size() ) = i;
	}

	//row
	for(size_t c = 0; col < puzzle.at(0).size(); col++){
		//get value
		val = puzzle.at(row).at(c)->getNum();

		//check if number
		if(val != 0){ 
			options->at(val % options->size()) = 0;
		}   
	}   

	//col
	for(size_t r = 0; r < puzzle.size(); r++){
		//get value
		val = puzzle.at(r).at(col)->getNum();

		//check if number
		if(val != 0){ 
			options->at(val % options->size()) = 0;
		}   

	}   

	//block
	size_t rowStart, colStart;
	rowStart = row/3 * 3;
	colStart = col/3 * 3;

	for(size_t r = rowStart; r < rowStart+3; r++){
		for(size_t c = colStart; c < colStart+3; c++){
			//get value
			val = puzzle.at(r).at(c)->getNum();

			//check if number
			if(val != 0){ 
				options->at(val % options->size()) = 0;
			}
		}   

	}   

	puzzle.at(row).at(col)->setOptions(options);

}

void Puzzle::printOptions(){
	for(size_t i = 0; i < puzzle.size(); i++){
		for(size_t j = 0; j < puzzle.at(i).size(); j++){
			puzzle.at(i).at(j)->printOptions();
		}
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	setters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
