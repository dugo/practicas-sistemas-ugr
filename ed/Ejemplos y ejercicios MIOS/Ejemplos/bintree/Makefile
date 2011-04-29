
CXX = g++

SRC = src
INCLUDE = include
LIB = lib
BIN = bin
OBJ = obj

# Opciones para compilar
CPPFLAGS = -Wall -g -I$(INCLUDE)

# Opciones para enlazar
LDFLAGS =  -L$(LIB) -lgraficos -lSDL_gfx -lSDL -lpthread


all : $(LIB)/libgraficos.a prueba1 prueba2 simetria

# Creacion de la biblioteca libgraficos.a
$(LIB)/libgraficos.a : $(OBJ)/graficos.o
	ar rsv $(LIB)/libgraficos.a $(OBJ)/graficos.o

# Compilando graficos.cpp
$(OBJ)/graficos.o : $(SRC)/graficos.cpp $(INCLUDE)/graficos.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/graficos.cpp -o $(OBJ)/graficos.o

# Compilando
$(OBJ)/bintreeutils.o : $(SRC)/bintreeutils.cpp $(INCLUDE)/bintreeutils.h $(INCLUDE)/graficos.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/bintreeutils.cpp -o $(OBJ)/bintreeutils.o

$(OBJ)/prueba1.o : $(SRC)/prueba1.cpp $(INCLUDE)/bintreeutils.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/prueba1.cpp -o $(OBJ)/prueba1.o

$(OBJ)/prueba2.o : $(SRC)/prueba2.cpp $(INCLUDE)/bintreeutils.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/prueba2.cpp -o $(OBJ)/prueba2.o

$(OBJ)/simetria.o : $(SRC)/simetria.cpp $(INCLUDE)/bintreeutils.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/simetria.cpp -o $(OBJ)/simetria.o

# Creacion del ejecutable
prueba1 : $(BIN)/prueba1
$(BIN)/prueba1 : $(OBJ)/bintreeutils.o $(OBJ)/prueba1.o $(LIB)/libgraficos.a
	$(CXX) $(OBJ)/bintreeutils.o $(OBJ)/prueba1.o $(LDFLAGS) -o $(BIN)/prueba1

prueba2 : $(BIN)/prueba2
$(BIN)/prueba2 : $(OBJ)/bintreeutils.o $(OBJ)/prueba2.o $(LIB)/libgraficos.a
	$(CXX) $(OBJ)/bintreeutils.o $(OBJ)/prueba2.o $(LDFLAGS) -o $(BIN)/prueba2

simetria : $(BIN)/simetria
$(BIN)/simetria : $(OBJ)/bintreeutils.o $(OBJ)/simetria.o $(LIB)/libgraficos.a
	$(CXX) $(OBJ)/bintreeutils.o $(OBJ)/simetria.o $(LDFLAGS) -o $(BIN)/simetria

# Borrar ficheros intermedios
clean :
	\rm -rf $(OBJ)/*.o $(LIB)/libgraficos.a \rm $(SRC)/*~ $(INCLUDE)/*~ Makefile~

# Borrar ficheros intermedios
mrproper : clean
	\rm -rf $(BIN)/*
