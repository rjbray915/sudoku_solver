#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void sort(vector<int> &contents, vector<int> tags);
int searchRow(vector<int> &contents, int key);
void readRow(vector<vector<int> > pPuzzle, vector<int> &contents, int row);
void readCol(vector<vector<int> > pPuzzle, vector<int> &contents, int col);
void readBlock(vector<vector<int> > pPuzzle, vector<int> &contents, int row, int col);

int main()
{
	vector<int> row(9);
	vector<int> col(9);
	vector<int> block(9);
	vector<vector<int> > puzzle{ {1, 3, 5, 7, 9, 2, 4, 6, 8},
		{3, 5, 7, 9, 2, 4, 6, 8, 1},
		{5, 7, 9, 2, 4, 6, 8, 1, 3},
		{7, 9, 2, 4, 6, 8, 1, 3, 5},
		{9, 2, 4, 6, 8, 1, 3, 5, 7},
		{2, 4, 6, 8, 1, 3, 5, 7, 9},
		{4, 6, 8, 1, 3, 5, 7, 9, 2},
		{6, 8, 1, 3, 5, 7, 9, 2, 4},
		{8, 1, 3, 5, 7, 9, 2, 4, 6} };

	readRow(puzzle, row, 5);
	readCol(puzzle, col, 7);
	readBlock(puzzle, block, 5, 4);

	//unsorted
	for(int i = 0; i < row.size(); i++)
	{
		cout << row.at(i)
			<< " " << col.at(i)
			<< " " << block.at(i)
			<< endl;
	}
}

void sort(vector<int> &contents, vector<int> tags)
{
	bool sorted = true;

	do{
		sorted = true;

		for(int c = 1; c < contents.size(); c++)
		{
			if(contents.at(c) < contents.at(c-1))
			{
				int tempC = contents.at(c);
				int tempT = tags.at(c);
				contents.at(c) = contents.at(c-1);
				contents.at(c-1) = tempC;
				tags.at(c) = tags.at(c-1);
				tags.at(c-1) = tempT;
				sorted = false;

				for(int x = 0; x < contents.size(); x++)
					printf("%u,", contents.at(x));
				printf("\n");
			}
		}
	}while(!sorted);

}

int searchRow(vector<int> &contents, int key)
{
	int max = contents.size()-1;
	int place = (max / 2);
	int move;

	do
	{
		move = (max - place)/2;
		if(move == 0)
			move = 1;

		if(key == contents.at(place))
		{
			return true;
		}
		else if(place == 0 || place == 8)
		{
			return false;
		}
		else if(key > contents.at(place))
		{
			place += move;
		}
		else if(key < contents.at(place))
		{
			max = place;
			place -= move;

		}
	} while(place >= 0 && place <= 8);
}


void readRow(vector<vector<int> > pPuzzle, vector<int> &contents, int row)
{
	for(int i = 0; i < contents.size(); i++)
	{
		contents.at(i) = pPuzzle.at(row).at(i);
	}
}

void readCol(vector<vector<int> > pPuzzle, vector<int> &contents, int col)
{
	for(int i = 0; i < contents.size(); i++)
	{
		contents.at(i) = pPuzzle.at(i).at(col);
	}
}

void readBlock(vector<vector<int> > pPuzzle, vector<int> &contents, int row, int col)
{
	int rowStart = row - row%3;
	int colStart = col - col%3;
	int i = 0;

	for(int r = rowStart; r < rowStart + 3; r++)
	{
		for(int c = colStart; c < colStart + 3; c++)
		{
			contents.at(i) = pPuzzle.at(r).at(c);
			i++;
		}
	}
}

