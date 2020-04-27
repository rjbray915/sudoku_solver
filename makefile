$CXXFLAGS = "-std=c++11 -Wall -Wextra"

#executable
bin/sudoku_solver: obj/Puzzle.o obj/Cell.o obj/sudoku_solver.o
	g++ $(CXXFLAGS) -o bin/sudoku_solver obj/Puzzle.o obj/Cell.o obj/sudoku_solver.o

#object code
obj/Cell.o: include/Puzzle.h include/Cell.h src/Puzzle.cpp src/Cell.cpp
	g++ $(CXXFLAGS) -c -o obj/Cell.o src/Cell.cpp

obj/Puzzle.o: include/Puzzle.h include/Cell.h src/Puzzle.cpp src/Cell.cpp
	g++ $(CXXFLAGS) -c -o obj/Puzzle.o src/Puzzle.cpp

obj/sudoku_solver.o: src/sudoku_solver.cpp
	g++ $(CXXFLAGS) -c -o obj/sudoku_solver.o src/sudoku_solver.cpp
