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
