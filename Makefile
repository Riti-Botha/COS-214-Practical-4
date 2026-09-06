taskforge:
	g++ -std=c++11 -g *.cpp -o taskforge

run: taskforge
	./taskforge

valgrind: taskforge
	valgrind --leak-check=full --show-leak-kinds=all ./taskforge

clean:
	rm -f taskforge
