FILES=clique_cover graph for_str
SRC=$(FILES:%=src/%.cpp)
OBJ=$(FILES:%=lib/%.o)
COMPILE=g++ -Iinclude

all: clique_cover

clique_cover: src/main.cpp libcc
	$(COMPILE) -o $@ $< -Llib/ -lcc

libcc: lib/libcc.a

lib/libcc.a: $(OBJ)
	ar rcs $@ $+

lib/%.o: src/%.cpp include/*.hpp
	$(COMPILE) -c $< -o $@
