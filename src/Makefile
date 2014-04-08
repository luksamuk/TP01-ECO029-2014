CXX  = g++
EXEC = TP01
D_FLAGS = -DDEBUG

# Remova D_FLAGS se não quiser rodar em modo DEBUG
CXX_FLAGS = $(D_FLAGS)

all: hash.o textpool.o main.o
	$(CXX) hash.o textpool.o main.o -o $(EXEC) $(CXX_FLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o $(CXX_FLAGS)

textpool.o: TextPool.cpp
	$(CXX) -c TextPool.cpp -o textpool.o $(CXX_FLAGS)

hash.o: Hash.cpp
	$(CXX) -c Hash.cpp -o hash.o $(CXX_FLAGS)

clean:
	rm -rf *.o *~
