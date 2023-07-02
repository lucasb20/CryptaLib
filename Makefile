all: hello

hello: main.o algs.o
	g++ -o hello main.o algs.o

main.o: main.cpp
	g++ -o main.o -c main.cpp

algs.o: algs.cpp
	g++ -o algs.o -c algs.cpp

clean:
	rm -f *.o hello