#COMPILE=clang++ -std=c++11 -stdlib=libc++ -g -Wall
COMPILE=g++ -g -static -std=gnu++0x -Wall

compile:
	$(COMPILE) date.cpp test.cpp -o test
	$(COMPILE) kattistime.cpp date.cpp jesus.cpp gregorian.cpp julian.cpp datetest.cpp -o datetest

test: compile
	./test
	./datetest
	make clean

all: test
	$(COMPILE) date.cpp -o lab2

clean:
	rm -f *.o
	rm -f lab2
	rm -f test
	rm -f *.dSym
	rm -f datetest
