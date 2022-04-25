#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#include "graph.h"
#endif
#include <stack>

class DFS{
    bool *visited;
    int time;
    int sccSize;
    Graph toUse;
    int numVertices;
    void DFS_run(Node *vertex, int index);
    void DFS2(Graph G, Node *vertex);
    public:    
    DFS(int size, Graph toUse);   
    void scc();
};