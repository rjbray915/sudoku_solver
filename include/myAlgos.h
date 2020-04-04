#include <iostream>
#include <vector>

bool oneOption(size_t i, size_t j, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessBlock(int row, int col, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessRow(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessCol(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessRelated(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessRelatedTwo(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);
bool assessRelatedThree(int rowCheck, int colCheck, vector<vector<int> > *puzzle, vector<vector<vector<int> > > *possibilities, bool &modified);