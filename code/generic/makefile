all:
	g++ -std=c++11 -Werror -Wall *.cpp -o generic

run: all
	./generic

memory:
	g++ -std=c++11 -Werror -Wall *.cpp -o generic
	valgrind --leak-check=full --show-leak-kinds=all ./generic
