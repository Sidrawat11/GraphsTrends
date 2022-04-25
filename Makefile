
gp:main.o graph.o utility.o DFS.o HashMap.o FW.o
	g++  main.o graph.o utility.o DFS.o HashMap.o FW.o -o gp

main.o: main.cpp defns.h
	g++ -c main.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

utility.o: utility.cpp utility.h
	g++ -c utility.cpp

BST.o: DFS.cpp DFS.h
	g++ -c DFS.cpp

HashMap.o: HashMap.cpp HashMap.h
	g++ -c HashMap.cpp

FW.o: FW.cpp FW.h
	g++ -c FW.cpp
clean:
	rm *.o earnings
