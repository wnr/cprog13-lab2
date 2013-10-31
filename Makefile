COMPILE=clang++ -std=c++11 -stdlib=libc++ -g -Wall

compile:
	$(COMPILE) Date.cpp test.cpp -o test

test: compile
	./test
	make clean

all: test
	$(COMPILE) Date.cpp -o lab2

clean:
	rm -f *.o
	rm -f lab2
	rm -f test
	rm -f *.dSym