
CXX = g++
CXXFLAGS = -std=c++17

SRC = main.cxx \
      comandos.cxx \
      ayuda.cxx \
      utilidades.cxx \
      sistema.cxx \
      genoma.cxx \
      secuencia.cxx \
      nodo_huffman.cxx \
      arbol_huffman.cxx \
      fabin.cxx

OBJ = $(SRC:.cxx=.o)

PROG = programa

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJ)

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROG)
