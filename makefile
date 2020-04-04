$CXXFLAGS = "-std=c++11 -Wall -Wextra"

test: ./src/sudoku_new.cpp
	g++ $CXXFLAGS -o test sudoku_solver.cpp