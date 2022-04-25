#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#endif

class Graph{
    void mergeSort(Node **arr, int start, int end);
    void mergeList(Node **arr, int left, int mid, int right);
public:
    Node **A;
    Pair **E;
    int *V;
    int size, edges_size;
    Graph();
    Graph(int size, int e_size,int arr[], Pair **eSet);
    void addEdge(int src, int dest);
    void printADJ();
    void outDegree();
    Node* getNode(int index);
    Graph getTranspose();
    Node **sortAdjancency();
};
