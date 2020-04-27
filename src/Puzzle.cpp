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
	int c = 0;
	ifstream iFS( readFile );
	
	//set number of rows
	puzzle.resize(9);

	while(iFS >> num){
		//c/9 gives row b/c groupings of 9, c%9 gives displacement
		puzzle.at(c%9).push_back( new Cell(num, c/9, c%9) );
		c++;
	}

	if(c != 81){
		throw( (string)"bad read file\n");
	}
}
