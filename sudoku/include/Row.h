#include <cstdint>

class Row
{
    private:
	uint8_t size;
	uint8_t rowStart;
	uint8_t contents[9];
	uint8_t tags[9];

    public:
	Row();
	Row(uint8_t row, uint8_t puzzle[9][9]);
	uint8_t* getContents();
	uint8_t* getTags();
	void sortRow();
	bool searchRow(uint8_t key);
};
