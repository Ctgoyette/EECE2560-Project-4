all: output run

run: output
	./output

output: main.o board.o gen_functions.o
	g++ main.o board.o gen_functions.o -o output

main.o: main.cpp
	g++ -c main.cpp

board.o: board.cpp
	g++ -c board.cpp

gen_functions.o: gen_functions.cpp
	g++ -c gen_functions.cpp