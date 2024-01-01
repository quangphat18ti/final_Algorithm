objects = SegmentTree.o

all: $(objects) exer_1.cpp
	g++ -o main.exe exer_1.cpp $(objects); ./main.exe

SegmentTree.o: SegmentTree.cpp SegmentTree.h
	g++ -c SegmentTree.cpp

test: $(objects)
	g++ -o unit_test.exe unit_tests.cpp $(objects); ./unit_test.exe

clean:
	rm -rf *.o *.exe 

