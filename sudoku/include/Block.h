#pragma once

class Block
{
	private:
		uint8_t rowStart;
		uint8_t colStart;
		uint8_t contents[9];
	public:
		Block();
		Block(uint8_t rowStart, uint8_t colStart, uint8_t puzzle[9][9]);
		uint8_t* getContents();
};
