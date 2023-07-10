all: hello

hello: main.o cifras.o rsa.o analise.o
	g++ -o hello main.o cifras.o rsa.o analise.o -lgmpxx -lgmp

main.o: main.cpp
	g++ -o main.o -c main.cpp

cifras.o: cifras.cpp
	g++ -o cifras.o -c cifras.cpp

rsa.o: rsa.cpp
	g++ -o rsa.o -c rsa.cpp

analise.o: analise.cpp
	g++ -o analise.o -c analise.cpp

clean:
	rm -f *.o hello