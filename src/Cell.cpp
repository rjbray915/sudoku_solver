#include "../include/Cell.h"

Cell::Cell(int num, size_t row, size_t col){
	this->num = num;
	this->row = row;
	this->col = col;
	this->options = NULL;

	if(num != 0){
		empty = false;;
	}
}

Cell& Cell::operator=(Cell& c){
	num = c.getNum();
	row = c.row;
	col = c.col;
	options = c.options;
	empty = c.isEmpty();

	return *this;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cell utility
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Cell::printOptions(){
	size_t i;
/*
	printf("size:%d\n", options->size() );
	printf("r:%u c:%u { ", row, col);
	for(i = 0; i < options->size(); i++){
		printf("%d, ", options->at(i) );
	}
	printf(" }\n");
*/
}

int Cell::searchOption(int num){
	int place = num % options->size();

	if(options->at(place) == num){
		return place; 
	}
	else{
		return -1;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	getters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Cell::getNum(){
	return num;
}

bool Cell::isEmpty(){
	return empty;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	setters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Cell::setOptions(vector<int>* options){
	this->options = options;
}
