#include "../include/Cell.h"

Cell::Cell(int num, size_t row, size_t col){
	this->num = num;
	this->row = row;
	this->col = col;
	this->options = NULL;

	if(num != 0){
		filled = true;
	}
}

Cell& Cell::operator=(Cell& c){
	num = c.num;
	row = c.row;
	col = c.col;
	options = c.options;
	filled = c.filled;

	return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cell utility
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Cell::printOptions(){
	size_t i;

	printf("r:%u c:%u { ", row, col);
	for(i = 0; i < options.size(); i++){
		printf("%d, ", options.at(i) );
	}
	printf(" }\n");

}

bool Cell::searchOption(int num, int left, int right){
	int middle = (left + right) / 2;

	if( options.at(middle) == num ){
		return true;
	}
	else if(left == right){
		return false;
	}
	else if(left > right){
		return false;
	}
	else{
		if( num > options.at(middle) ){
			return searchOption(num, middle+1, right);
		}
		else{
			return searchOption(num, left, middle-1);
		}
	}
}
