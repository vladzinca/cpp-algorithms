CXX = g++

build:
	g++ -o walsh walsh.cpp
	g++ -o statistics statistics.cpp
	g++ -o prinel prinel.cpp
	g++ -o crypto crypto.cpp

run-p1:
	./walsh

run-p2:
	./statistics

run-p3:
	./prinel

run-p4:
	./crypto

.PHONY: clean
clean :
	rm -f walsh statistics prinel crypto
	rm -f *.out

