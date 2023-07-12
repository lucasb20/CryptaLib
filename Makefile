CXX = g++
CXXFLAGS = -lgmpxx -lgmp
OBJS = main.o cifras.o rsa.o analise.o
EXE = hello

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f *.o $(EXE)
