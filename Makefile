CC=g++

LFLAGS=-framework OpenGL -framework GLUT -framework Cocoa

PROD=tree

OBJ=main.o Branch.o Vector.o Input.o

.PHONY: all
all: $(PROD)

.PHONY: clean
clean:
	rm $(OBJ) $(PROD)

$(PROD): $(OBJ)
	g++ -o $@ $^ $(LFLAGS)

%.o: %.cpp
	g++ -c -o $@ $<
