#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../include/Puzzle.h"
using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	edit notes:
		* needs to add reading from fstream

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
		if(num < 1 || num > 9){
			throw ( (string)"bad read file\n" );
		}

		puzzle.at(count%9).push_back( new Cell(num, count/9, count%9) );
		count++;
	}

	if(count != 81){
		throw( (string)"bad read file\n");
	}
}
