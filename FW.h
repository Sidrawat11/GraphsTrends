#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#include "graph.h"
#endif

class FW{
    int N;
    int **adjMatrix;
public:
    FW(Graph G, int N);
    void printMatrix();
    int floyd_Warshal();
};