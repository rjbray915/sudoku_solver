#pragma once

class Puzzle
{
    private:
        Row rows[9];
        Collumn cols[9];
        uint8_t puzzle[9][9];

    public: 
		Puzzle();
        Puzzle(uint8_t parPuzzle[9][9]);
};

