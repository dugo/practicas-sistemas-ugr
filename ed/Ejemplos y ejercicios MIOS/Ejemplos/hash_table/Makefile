
OBJ = obj
SRC = src
BIN = bin
INC = include

all : ejemplo_thash

ejemplo_thash : $(BIN)/ejemplo_thash $(BIN)/ejemplo2_thash
$(BIN)/ejemplo_thash : $(OBJ)/ejemplo_thash.o
	g++ -o $(BIN)/ejemplo_thash $(OBJ)/ejemplo_thash.o

ejemplo2_thash : $(BIN)/ejemplo2_thash
$(BIN)/ejemplo2_thash : $(OBJ)/ejemplo2_thash.o
	g++ -o $(BIN)/ejemplo2_thash $(OBJ)/ejemplo2_thash.o

$(OBJ)/ejemplo_thash.o : $(SRC)/ejemplo_thash.cpp $(INC)/hash_table.h $(INC)/hash_table.template
	g++ -c -o $(OBJ)/ejemplo_thash.o $(SRC)/ejemplo_thash.cpp -I$(INC)/

$(OBJ)/ejemplo2_thash.o : $(SRC)/ejemplo2_thash.cpp $(INC)/hash_table.h $(INC)/hash_table.template
	g++ -c -o $(OBJ)/ejemplo2_thash.o $(SRC)/ejemplo2_thash.cpp -I$(INC)/

.PHONY : clean
clean :
	rm -rf $(OBJ)/*.o

.PHONY : mrproper
mrproper : clean
	rm -rf $(BIN)/*
