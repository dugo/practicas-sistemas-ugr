
CXX = g++

SRC = src
INC = src
OBJ = src
LIB = src
BIN = bin

CCFLAGS = -Wall -g
LDFLAGS = -L$(LIB) -lVT

all : pathfinder

pathfinder : $(BIN)/pathfinder
$(BIN)/pathfinder : $(OBJ)/pathfinder.o $(LIB)/libVT.a
	$(CXX) $(OBJ)/pathfinder.o $(LDFLAGS) -o $(BIN)/pathfinder

$(OBJ)/pathfinder.o : $(SRC)/pathfinder.cc $(INC)/MapItem.hh $(INC)/Crossroads.hh $(INC)/Stretch.hh $(INC)/CGraph.cc $(INC)/VTio.hh $(INC)/VTalg.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/pathfinder.cc -o $(OBJ)/pathfinder.o

$(LIB)/libVT.a : $(OBJ)/MapItem.o $(OBJ)/Crossroads.o $(OBJ)/Stretch.o $(OBJ)/VTio.o $(OBJ)/VTalg.o
	ar rsv $(LIB)/libVT.a $(OBJ)/MapItem.o $(OBJ)/Crossroads.o $(OBJ)/Stretch.o $(OBJ)/VTio.o $(OBJ)/VTalg.o

$(OBJ)/MapItem.o : $(SRC)/MapItem.cc $(INC)/MapItem.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/MapItem.cc -o $(OBJ)/MapItem.o

$(OBJ)/Crossroads.o : $(SRC)/Crossroads.cc $(INC)/Crossroads.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/Crossroads.cc -o $(OBJ)/Crossroads.o

$(OBJ)/Stretch.o : $(SRC)/Stretch.cc $(INC)/Stretch.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/Stretch.cc -o $(OBJ)/Stretch.o

$(OBJ)/VTio.o : $(SRC)/VTio.cc $(INC)/VTio.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/VTio.cc -o $(OBJ)/VTio.o

$(OBJ)/VTalg.o : $(SRC)/VTalg.cc $(INC)/VTalg.hh
	$(CXX) $(CCFLAGS) -c -I$(INC) $(SRC)/VTalg.cc -o $(OBJ)/VTalg.o

.PHONY : clean
clean :
	\rm -vrf $(OBJ)/*.o $(LIB)/*.a

.PHONY : mrproper
mrproper : clean
	\rm -vrf $(BIN)/*
