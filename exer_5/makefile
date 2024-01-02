run: main
	./main

object = exer_5.cpp Hash.h 
main: $(object)
	g++ -o main $(object) 

clean:
	rm main

test_object = unit_test.cpp Hash.h
unit_test: $(test_object)
	g++ -o unit_test $(test_object)
	./unit_test
	rm unit_test