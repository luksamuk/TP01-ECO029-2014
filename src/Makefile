CXX  = g++
EXEC = TP01
D_FLAGS = -g -DDEBUG

# Remova D_FLAGS se não quiser rodar em modo DEBUG
CXX_FLAGS = $(D_FLAGS)
#CXX_FLAGS = -O3

all: hash.o list.o textpool.o main.o
	$(CXX) hash.o list.o textpool.o main.o -o $(EXEC) $(CXX_FLAGS)

test: lista

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o $(CXX_FLAGS)

textpool.o: TextPool.cpp
	$(CXX) -c TextPool.cpp -o textpool.o $(CXX_FLAGS)

hash.o: Hash.cpp
	$(CXX) -c Hash.cpp -o hash.o $(CXX_FLAGS)

# Testes
lista: lista.o list.o
	$(CXX) lista.o list.o -o tests/lista $(CXX_FLAGS)
	
list.o: List.cpp
	$(CXX) -c List.cpp -o list.o $(CXX_FLAGS)
lista.o: tests/lista.cpp
	$(CXX) -c tests/lista.cpp -o lista.o $(CXX_FLAGS)

clean:
	rm -rf *.o *~
