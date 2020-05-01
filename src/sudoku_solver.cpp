#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include "../include/myAlgos.h"
#include "../include/Puzzle.h"
using namespace std;

/*notes
 * should get rid of all of the 0's and just have a find function.
 * it would be a lot faster I think b/c it is still checking all 9 in the possibility list.






 */

//prototypes
vector<int> possible(size_t r, size_t c, vector<vector<int> > *puzzle);
void updatePossible(size_t i, size_t j, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, int possibility);
void printOptions(vector<int> *options);
void assessBlock(int row, int col, vector<vector<int> > *puzzle);

bool pairEliminateRow(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);

int main()
{

	/*******************************************8


		testing my new classes

	 **********************************************/
	Puzzle* puzz;

	try{
		puzz = new Puzzle( (string)("textPuzzles/test1.txt") );
	} catch(string s){
		printf("%s\n", s.c_str() );
		return -1;
	}

	//return for now
	printf("it worked!\n");
	return 0;

	vector<vector<int> > puzzle{{4,0,0,0,0,0,9,3,8},
		{0,3,2,0,9,4,1,0,0},
		{0,9,5,3,0,0,2,4,0},
		{3,7,0,6,0,9,0,0,4},
		{5,2,9,0,0,1,6,7,3},
		{6,0,4,7,0,3,0,9,0},
		{9,5,7,0,0,8,3,0,0},
		{0,0,3,9,0,0,4,0,0},
		{2,4,0,0,3,0,7,0,9}};
	vector<vector<vector<int> > > possibilities;
	size_t i, j;
	bool modified = false;

	//resizing and assigning possibilities list
	possibilities.resize(puzzle.size());
	for(i = 0; i < possibilities.size(); i++){

		possibilities.at(i).resize(puzzle.at(0).size());

		for(j = 0; j < possibilities.at(0).size(); j++){
			possibilities.at(i).at(j) = possible(i, j, &puzzle);
		}
	}

	int c = 0;
	do{
		//modified = false;

		for(i = 0; i < possibilities.size(); i++){
			for(j = 0; j < possibilities.at(0).size(); j++){
				//if(i == 0){
				///*dlt*/ printf("row:%u  col:%u", i, j);
				///*dlt*/printf("before:");
				///*dlt*/printOptions(&possibilities.at(i).at(j));
				//delete possibilities before trying stuff
				//}

				///*dlt*/printf("after:");
				//	printOptions(&possibilities.at(i).at(j));

				//randomNum = rand() % 3;
				//switch(randomNum){
				//	case 0: 
				if(c%2 == 0){
					//assessRelated(i, j, &puzzle, &possibilities, modified);
					//assessRelatedTwo(i, j, &puzzle, &possibilities, modified);
					//assessRelatedThree(i, j, &puzzle, &possibilities, modified);
					if(pairEliminateRow(i, j, &puzzle, &possibilities, modified)) printf("pair row success  %u\n", i);
				} else{	
					if(oneOption(i, j, &puzzle, &possibilities, modified)){
						updatePossible(i, j, &puzzle, &possibilities, puzzle.at(i).at(j));
						///*dlt*/ printf("row:%u  col:%u", i, j);
						//printf("yay one\n");
						///*dlt*/printf("before:");
						///*dlt*/printOptions(&possibilities.at(i).at(j));
						///*dlt*/printf("after:");
						//printOptions(&possibilities.at(i).at(j));
					}
					else if(assessBlock(i, j, &puzzle, &possibilities, modified)){
						updatePossible(i, j, &puzzle, &possibilities, puzzle.at(i).at(j));
						///*dlt*/ printf("row:%u  col:%u", i, j);
						//printf("yay block\n");
						///*dlt*/printf("before:");
						///*dlt*/printOptions(&possibilities.at(i).at(j));
						//	/*dlt*/printf("after:");
						//	printOptions(&possibilities.at(i).at(j));
					}
					else if(assessRow(i, j, &puzzle, &possibilities, modified)){
						updatePossible(i, j, &puzzle, &possibilities, puzzle.at(i).at(j));
					}
					else if(assessCol(i, j, &puzzle, &possibilities, modified)){
						updatePossible(i, j, &puzzle, &possibilities, puzzle.at(i).at(j));
					}
				}
			}
			}
		}while(c < 100);
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

	void updatePossible(size_t row, size_t col, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, int possibility){
		size_t i, j, blockRow, blockCol;

		//row
		i = row;
		for(j = 0; j < possibilities->at(i).size(); j++){
			possibilities->at(i).at(j).at(possibility%9) = 0;

		}

		//col
		j = col;
		for(i = 0; i < possibilities->size(); i++){
			possibilities->at(i).at(j).at(possibility%9) = 0;
		}

		//block
		blockRow = (row / 3) * 3;
		blockCol = (col / 3) * 3;
		for(i = blockRow; i < blockRow+3; i++){
			for(j = blockCol; j < blockCol+3; j++){
				possibilities->at(i).at(j).at(possibility%9) = 0;
			}
		}
	}

	bool oneOption(size_t i, size_t j, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
		size_t k;
		int chosenOpt = 0, countOption = 0;

		for(k = 0; k < possibilities->at(i).at(j).size(); k++){

			if(possibilities->at(i).at(j).at(k) != 0){
				chosenOpt = possibilities->at(i).at(j).at(k);
				countOption++;
			}

			if(countOption > 1){
				return false;
			}
		}

		if(chosenOpt != 0){
			puzzle->at(i).at(j) = chosenOpt;
			updatePossible(i, j, puzzle, possibilities, chosenOpt%9);
			modified = true;
			return true;
		} else{
			return false;
		}
	}


	bool assessBlock(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
		size_t i, j, possCheck, countOption;
		int rowStart, colStart;

		rowStart = (rowCheck / 3) * 3;
		colStart = (colCheck / 3) * 3;
		for(possCheck = 0; possCheck < possibilities->at(0).at(0).size(); possCheck++){

			if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){
				countOption = 0;

				for(i = rowStart; i < rowStart+3; i++){
					for(j = colStart; j < colStart+3; j++){

						///*dlt*/ printf("poss:%d check:%d count:%d\n", possibilities->at(rowCheck).at(colCheck).at(possCheck), possibilities->at(i).at(j).at(possCheck), countOption);
						if(possibilities->at(i).at(j).at(possCheck) != 0 && !(i == rowCheck && j == colCheck)){
							//printf("urmom");
							countOption++;
							break;
						}

					}

					//need to move onto next
					if(countOption != 0){
						break;
					}
				}

				//no other has that option
				if(countOption == 0){
					puzzle->at(rowCheck).at(colCheck) = possibilities->at(rowCheck).at(colCheck).at(possCheck);
					//modified = true;
					return true;
				}
			}
		}

		return false;
	}

	bool assessRow(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
		size_t i, j, possCheck, countOption;
		int rowStart, colStart;

		rowStart = rowCheck;
		colStart = 0;
		for(possCheck = 0; possCheck < possibilities->at(0).at(0).size(); possCheck++){

			if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){
				countOption = 0;

				i = rowStart;
				for(j = colStart; j < possibilities->at(rowStart).size(); j++){

					///*dlt*/ printf("poss:%d check:%d count:%d\n", possibilities->at(rowCheck).at(colCheck).at(possCheck), possibilities->at(i).at(j).at(possCheck), countOption);
					if(possibilities->at(i).at(j).at(possCheck) != 0 && j != colCheck){
						//printf("urmom");
						countOption++;
						break;
					}

				}

				//need to move onto next
				if(countOption != 0){
					break;
				}
			}

			//no other has that option
			if(countOption == 0){
				printf("success row\n");
				puzzle->at(rowCheck).at(colCheck) = possibilities->at(rowCheck).at(colCheck).at(possCheck);
				//modified = true;
				return true;
			}
		}

		return false;
	}

	bool assessCol(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
		size_t i, j, possCheck, countOption;
		int rowStart, colStart;

		rowStart = 0;
		colStart = colCheck;
		for(possCheck = 0; possCheck < possibilities->at(0).at(0).size(); possCheck++){

			if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){
				countOption = 0;

				j = colStart;
				for(i = rowStart; i < possibilities->size(); i++){

					///*dlt*/ printf("poss:%d check:%d count:%d\n", possibilities->at(rowCheck).at(colCheck).at(possCheck), possibilities->at(i).at(j).at(possCheck), countOption);
					if(possibilities->at(i).at(j).at(possCheck) != 0 && i != rowCheck){
						//printf("urmom");
						countOption++;
						break;
					}

				}

				//need to move onto next
				if(countOption != 0){
					break;
				}
			}

			//no other has that option
			if(countOption == 0){
				printf("success col\n");
				puzzle->at(rowCheck).at(colCheck) = possibilities->at(rowCheck).at(colCheck).at(possCheck);
				//modified = true;
				return true;
			}
		}

		return false;
	}

	bool assessRelated(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
		//vars
		size_t i, j, possCheck, blockRowOrig, blockColOrig, blockRowCheck, blockColCheck;
		size_t countOptionRowsCols, countOptionInRowCol, optionRowCol;

		//getting originating block properties
		blockRowOrig = (rowCheck / 3) * 3;
		blockColOrig = (colCheck / 3) * 3;

		//iterate through possibilities
		for(possCheck = 0; possCheck < possibilities->at(rowCheck).at(colCheck).size(); possCheck++){
			if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				 * start with "block row" that is related
				 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				 */
				//loop to set the blockCol to assess
				//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
				blockColCheck = (blockColOrig + 3) % puzzle->at(0).size();
				while(blockColCheck != blockColOrig){

					countOptionRowsCols = 0;

					//loop for rows to iterate through in block
					for(i = blockRowOrig; i < blockRowOrig+3; i++){
						countOptionInRowCol = 0;

						//loop for cols to iteratue through in block
						//i am modding by puzzle row size to make the loop circular.
						//that way it goes ahead one every time, and if the starting 
						//block is at the end, it will circle back around.
						for(j = blockColCheck; j < blockColCheck+3; j++){
							///*dlt*/printf("block:%u row:%u col:%u\n", blockColCheck, i, j);
							if(possibilities->at(i).at(j).at(possCheck) != 0){
								optionRowCol = i;
								countOptionInRowCol++;
								break;
							}
						}

						if(countOptionInRowCol != 0){
							countOptionRowsCols++;
						}
					}

					if(countOptionRowsCols == 1){
						//printf("reached row option deletion\n");
						i = optionRowCol;
						for(j = blockColOrig; j < blockColOrig+3; j++){
							possibilities->at(i).at(j).at(possCheck) = 0;
						}

						//need to continue the loop in main
						//modified = true;
						return true;
					}

					//incrementing block column to check
					blockColCheck = (blockColCheck + 3) % puzzle->at(0).size();
				}


				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				 * next is the "block column" that is related
				 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				 */
				//loop to set the blockRow to assess
				//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
				blockRowCheck = (blockRowOrig + 3) % puzzle->at(0).size();
				while(blockRowCheck != blockRowOrig){

					countOptionRowsCols = 0;

					//loop for rows to iterate through in block
					for(j = blockColOrig; j < blockColOrig+3; j++){
						countOptionInRowCol = 0;

						//loop for cols to iteratue through in block
						//i am modding by puzzle row size to make the loop circular.
						//that way it goes ahead one every time, and if the starting 
						//block is at the end, it will circle back around.
						for(i = blockRowCheck; i < blockRowCheck+3; i++){
							///*dlt*/printf("blockRow:%u row:%u col:%u\n", blockRowCheck, i, j);
							if(possibilities->at(i).at(j).at(possCheck) != 0){
								optionRowCol = j;
								countOptionInRowCol++;
								break;
							}
						}

						if(countOptionInRowCol != 0){
							countOptionRowsCols++;
						}
					}

					if(countOptionRowsCols == 1){
						//printf("reached collumn option deletion\n");
						j = optionRowCol;
						for(i = blockRowOrig; i < blockRowOrig+3; i++){
							possibilities->at(i).at(j).at(possCheck) = 0;
						}

						//need to continue the loop in main
						//modified = true;
						return true;
					}

					//incrementing block column to check
					blockRowCheck = (blockRowCheck + 3) % puzzle->at(0).size();
				}

			}
			}


			return false;
			}


			bool assessRelatedTwo(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
				//vars
				size_t i, j, possCheck, blockRowOrig, blockColOrig, blockRowCheck, blockColCheck;
				size_t countOptionRowsCols1, countOptionRowsCols2, countOptionInRowCol, optionRowCol1, optionRowCol2;
				size_t numBlock = 0;
				bool matchingFirst, matchingSecond;


				//getting originating block properties
				blockRowOrig = (rowCheck / 3) * 3;
				blockColOrig = (colCheck / 3) * 3;

				//iterate through possibilities
				for(possCheck = 0; possCheck < possibilities->at(rowCheck).at(colCheck).size(); possCheck++){
					if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){
						///*dlt*/ printf("possible:%d\n", possibilities->at(rowCheck).at(colCheck).at(possCheck));
						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						 * start with "block row" that is related
						 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						 */
						//loop to set the blockCol to assess
						//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
						blockColCheck = (blockColOrig + 3) % puzzle->at(0).size();
						numBlock = 0;
						matchingFirst = false;
						matchingSecond = false;
						optionRowCol1 = 0;
						optionRowCol2 = 0;
						countOptionRowsCols1 = 0;
						countOptionRowsCols2 = 0;

						while(blockColCheck != blockColOrig){

							//loop for rows to iterate through in block
							for(i = blockRowOrig; i < blockRowOrig+3; i++){
								countOptionInRowCol = 0;

								//loop for cols to iteratue through in block
								//i am modding by puzzle row size to make the loop circular.
								//that way it goes ahead one every time, and if the starting 
								//block is at the end, it will circle back around.
								for(j = blockColCheck; j < blockColCheck+3; j++){
									///*dlt*/if(rowCheck == 4) printf("block:%u row:%u col:%u\n", blockColCheck, i, j);
									if(possibilities->at(i).at(j).at(possCheck) != 0){
										//printf("yes\n");	
										countOptionInRowCol++;
										//break;
									}
								}

								if(countOptionInRowCol != 0){
									if(numBlock == 0){
										countOptionRowsCols1++;
									}else{
										countOptionRowsCols2++;
									}

									//if first block
									if(numBlock == 0){
										//if(rowCheck == 4) printf("block 0 before row:%u optionRow1:%u optionRow2:%u\n", i, optionRowCol1, optionRowCol2);

										if(countOptionRowsCols1 == 1 || countOptionRowsCols2 == 1){
											optionRowCol1 = i;
										}else if(countOptionRowsCols1 == 2 || countOptionRowsCols2 == 2){
											optionRowCol2 = i;
										}

										//if(rowCheck == 4) printf("block 0 after row:%u optionRow1:%u optionRow2:%u\n", i, optionRowCol1, optionRowCol2);
									} else{
										//if(rowCheck == 4) printf("block 1 before row:%u optionRow1:%u optionRow2:%u first:%d second:%d\n", i, optionRowCol1, optionRowCol2, matchingFirst, matchingSecond);

										if(optionRowCol1 != 0 && (countOptionRowsCols1 == 1 || countOptionRowsCols2 == 1) && optionRowCol1 == i){
											matchingFirst = true;
										}
										else if(optionRowCol2 != 0 && (countOptionRowsCols1 == 2 || countOptionRowsCols2 == 2) && optionRowCol2 == i){
											matchingSecond = true;
										}else{
											matchingFirst = false;
											matchingSecond = false;
										}

										//if(rowCheck == 4) printf("block 1 before row:%u optionRow1:%u optionRow2:%u first:%d second:%d\n", i, optionRowCol1, optionRowCol2, matchingFirst, matchingSecond);
									}
								}
							}


							//incrementing block column to check
							blockColCheck = (blockColCheck + 3) % puzzle->at(0).size();
							numBlock++;
						}

						//delete them if true
						if((countOptionRowsCols1 == 2) && (countOptionRowsCols2 == 2) && (matchingFirst == true) && (matchingSecond == true)){
							//printf("row delte\n");
							//first row to delete options
							i = optionRowCol1;
							for(j = blockColOrig; i < blockColOrig+3; i++){
								possibilities->at(i).at(j).at(possCheck) = 0;
							}

							//second row to delete options
							i = optionRowCol2;
							for(j = blockColOrig; j < blockColOrig+3; j++){
								possibilities->at(i).at(j).at(possCheck) = 0;
							}

							//modified = true;
							return true;
						}

						/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						 * next is the "block column" that is related
						 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						 */
						//loop to set the blockRow to assess
						//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
						blockRowCheck = (blockRowOrig + 3) % puzzle->at(0).size();
						numBlock = 0;
						matchingFirst = false;
						matchingSecond = false;
						optionRowCol1 = 0;
						optionRowCol2 = 0;
						countOptionRowsCols1 = 0;
						countOptionRowsCols2 = 0;
						while(blockRowCheck != blockRowOrig){

							//loop for rows to iterate through in block
							for(j = blockColOrig; j < blockColOrig+3; j++){
								countOptionInRowCol = 0;

								//loop for cols to iteratue through in block
								//i am modding by puzzle row size to make the loop circular.
								//that way it goes ahead one every time, and if the starting 
								//block is at the end, it will circle back around.
								for(i = blockRowCheck; i < blockRowCheck+3; i++){
									///*dlt*/if(i == 4) printf("blockRow:%u row:%u col:%u\n", blockRowCheck, i, j);
									if(possibilities->at(i).at(j).at(possCheck) != 0){
										countOptionInRowCol++;
										break;
									}
								}

								if(countOptionInRowCol != 0){
									if(numBlock == 0){
										countOptionRowsCols1++;
									}else{
										countOptionRowsCols2++;
									}

									//if first block
									if(numBlock == 0){
										if(countOptionRowsCols1 == 1 || countOptionRowsCols2 == 1){
											optionRowCol1 = j;
										}else if(countOptionRowsCols1 == 2 || countOptionRowsCols2 == 2){
											optionRowCol2 = j;
										}

										//if(rowCheck == 3) printf("block 0 row:%u optionCol1:%u optionCol2:%u\n", i, optionRowCol1, optionRowCol2);
									} else{
										if(optionRowCol1 != 0 && (countOptionRowsCols1 == 1 || countOptionRowsCols2 == 1) && optionRowCol1 == j){
											matchingFirst = true;
										}
										else if(optionRowCol2 != 0 && (countOptionRowsCols1 == 2 || countOptionRowsCols2 == 2) && optionRowCol2 == j){
											matchingSecond = true;
										}

										//if(rowCheck == 3) printf("block 1 row:%u optionCol1:%u optionCol2:%u\n", i, optionRowCol1, optionRowCol2);
									}
								}
							}

							//incrementing block column to check
							blockRowCheck = (blockRowCheck + 3) % puzzle->at(0).size();
							numBlock++;
						}

						//delete the possibilities
						if(countOptionRowsCols1 == 2 && countOptionRowsCols2 == 2&& matchingFirst == true && matchingSecond == true){
							//printf("col delete\n");
							//first row to delete options
							j = optionRowCol1;
							for(i = blockRowOrig; i < blockRowOrig+3; i++){
								possibilities->at(i).at(j).at(possCheck) = 0;
							}

							//second row to delete options
							j = optionRowCol2;
							for(i = blockRowOrig; i < blockRowOrig+3; i++){
								possibilities->at(i).at(j).at(possCheck) = 0;
							}

							//modified = true;
							return true;
						}

					}
					}
					}

					bool assessRelatedThree(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
						//vars
						size_t i, j, possCheck, blockRowOrig, blockColOrig, blockRowCheck, blockColCheck;
						size_t countOptionInRowCol1, countOptionInRowCol2, numBlock;

						//getting originating block properties
						blockRowOrig = (rowCheck / 3) * 3;
						blockColOrig = (colCheck / 3) * 3;

						//iterate through possibilities
						for(possCheck = 0; possCheck < possibilities->at(rowCheck).at(colCheck).size(); possCheck++){
							if(possibilities->at(rowCheck).at(colCheck).at(possCheck) != 0){

								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								 * start with "block row" that is related
								 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								 */
								//loop to set the blockCol to assess
								//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
								blockColCheck = (blockColOrig + 3) % puzzle->at(0).size();
								numBlock = 0;
								countOptionInRowCol1 = 0;
								countOptionInRowCol2 = 0;
								while(blockColCheck != blockColOrig){

									//only searching row of possibility
									i = rowCheck;

									//loop for cols to iteratue through in block
									//i am modding by puzzle row size to make the loop circular.
									//that way it goes ahead one every time, and if the starting 
									//block is at the end, it will circle back around.
									for(j = blockColCheck; j < blockColCheck+3; j++){
										///*dlt*/printf("block:%u row:%u col:%u\n", blockColCheck, i, j);
										if(possibilities->at(i).at(j).at(possCheck) != 0){
											if(numBlock == 0){
												countOptionInRowCol1++;
											}else{
												countOptionInRowCol2++;
											}
											break;
										}
									}

									//incrementing block column to check
									blockColCheck = (blockColCheck + 3) % puzzle->at(0).size();
									numBlock++;
								}

								if(countOptionInRowCol1 == 0 && countOptionInRowCol2 == 0){
									//printf("THREE reached row option deletion\n");
									for(i = blockRowOrig; i < blockRowOrig+3; i++){
										//FIX THIS UGLY ASS LOOP
										if(i != rowCheck){
											for(j = blockColOrig; j < blockColOrig+3; j++){
												possibilities->at(i).at(j).at(possCheck) = 0;
											}
										}
									}
									//need to continue the loop in main
									//modified = true;
									return true;
								}


								/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								 * next is the "block column" that is related
								 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								 */
								//loop to set the blockRow to assess
								//for(blockColCheck = blockColOrig + 3; (blockColCheck % puzzle->at(0).size()) != blockColOrig; blockColCheck += 3){
								blockRowCheck = (blockRowOrig + 3) % puzzle->at(0).size();
								numBlock = 0;
								countOptionInRowCol1 = 0;
								countOptionInRowCol2 = 0;
								while(blockRowCheck != blockRowOrig){

									//only searching row of possibility
									j = colCheck;

									//loop for cols to iteratue through in block
									//i am modding by puzzle row size to make the loop circular.
									//that way it goes ahead one every time, and if the starting 
									//block is at the end, it will circle back around.
									for(i = blockRowCheck; i < blockRowCheck+3; i++){
										if(possibilities->at(i).at(j).at(possCheck) != 0){
											if(numBlock == 0){
												countOptionInRowCol1++;
											}else{
												countOptionInRowCol2++;
											}

											break;
										}
									}

									//incrementing block column to check
									blockRowCheck = (blockRowCheck + 3) % puzzle->at(0).size();
									numBlock++;
								}

								if(countOptionInRowCol1 == 0 && countOptionInRowCol2 == 0){
									//printf("THREE reached row option deletion\n");
									for(j = blockColOrig; j < blockColOrig+3; j++){
										//FIX THIS UGLY ASS LOOP
										if(j != colCheck){
											for(i = blockRowOrig; i < blockRowOrig+3; i++){
												possibilities->at(i).at(j).at(possCheck) = 0;
											}
										}
									}
									//need to continue the loop in main
									//modified = true;
									return true;
								}

							}
							}


							return false;
							}

							bool pairEliminateRow(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified){
								size_t i, j, pairFirst, pairSecond, countPairs, countOptions, rowFound, colFound;

								//check that this cell only has two options
								countOptions = 0;
								size_t checkOptions;
								for(checkOptions = 0; checkOptions < possibilities->at(rowCheck).at(colCheck).size(); checkOptions++){
									if(possibilities->at(rowCheck).at(colCheck).at(checkOptions) != 0){
										countOptions++;
									}
								}
								//not only two options in cell, done
								if(countOptions != 2){
									return false;
								}

								//row
								for(pairFirst = 0; pairFirst < possibilities->at(rowCheck).at(colCheck).size(); pairFirst++){
									if(possibilities->at(rowCheck).at(colCheck).at(pairFirst) != 0){
										pairSecond = (pairFirst+1) % 9;

										while(pairSecond != pairFirst){
											if(possibilities->at(rowCheck).at(colCheck).at(pairSecond) != 0){
												countPairs = 0;
												i = rowCheck;
												j = (colCheck+1) % 9;

												while(j != colCheck){
													if(possibilities->at(i).at(j).at(pairFirst) != 0
															&& possibilities->at(i).at(j).at(pairSecond) != 0){
														//check that theyre the only possibilities
														countOptions = 0;
														size_t checkOptions;
														for(checkOptions = 0; checkOptions < possibilities->at(i).at(j).size(); checkOptions++){
															if(possibilities->at(i).at(j).at(checkOptions) != 0){
																countOptions++;
															}
														}

														if(countOptions == 2){
															countPairs++;
															rowFound = rowCheck;
															colFound = j;
														}
													}

													j = (j+1) % 9;
												}

												//eliminate possibilities from other cells
												if(countPairs == 1){
													/*dlt*/printf("pairFirst: %u pairSecond: %u\n", pairFirst, pairSecond);

													i = rowFound;
													for(j = 0; j < possibilities->at(rowCheck).size(); j++){
														if(j != colFound && j != colCheck){
															possibilities->at(i).at(j).at(pairFirst) = 0;
															possibilities->at(i).at(j).at(pairSecond) = 0;
														}
													}

													return true;
												}
											}
											pairSecond = (pairSecond+1) % 9;
										}
									}
								}

								return false;

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
