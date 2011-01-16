CCFLAGS = -Wall

all: mainBK mainBB

mainBK: mainBK.o	bombillas_BK.o
	g++ $(CCFLAGS) mainBK.o bombillas_BK.o -o mainBK

mainBB: mainBB.o	bombillas_BB.o
	g++ $(CCFLAGS) mainBB.o bombillas_BB.o -o mainBB

mainBK.o: mainBK.cpp
	g++ $(CCFLAGS) mainBK.cpp -c -o mainBK.o

mainBB.o: mainBB.cpp
	g++ $(CCFLAGS) mainBB.cpp -c -o mainBB.o

bombillas_BK.o: bombillas_BK.cpp
	g++ $(CCFLAGS) bombillas_BK.cpp -c -o bombillas_BK.o

bombillas_BB.o: bombillas_BB.cpp
	g++ $(CCFLAGS) bombillas_BB.cpp -c -o bombillas_BB.o


mrproper:
	rm *.o mainBK mainBB
