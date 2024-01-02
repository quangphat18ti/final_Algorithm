run: main 
	./main 

main: exer_17.cpp
	g++ -std=c++11 exer_17.cpp -o main

clean:
	rm -f main test

test: test.cpp 
	g++ -std=c++11 test.cpp -o test
	./test
	rm -f test