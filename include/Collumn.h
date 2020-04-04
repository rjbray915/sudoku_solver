#pragma once

class Collumn
{
	private:
		uint8_t size;
		uint8_t colStart;
		uint8_t contents[9];
		uint8_t tags[9];

	public:
		Collumn();
		Collumn(uint8_t col, uint8_t puzzle[9][9]);
		uint8_t* getContents();
		uint8_t* getTags();
		void sortCol();
		bool searchCol(uint8_t key);
};

