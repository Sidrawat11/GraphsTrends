#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#include "graph.h"
#endif
#include "DFS.h"

DFS ::DFS(int size, Graph toUse)
{
    numVertices = size;
    this->toUse = toUse;
    visited = new bool[numVertices];
    time = 0;
    sccSize = 1;
    for (int i = 0; i < numVertices; i++)
    {
        toUse.A[i]->d = 0;
        toUse.A[i]->f = 0;
        visited[i] = false;
    }
}

void DFS ::DFS_run(Node *vertex, int index)
{
    time = time + 1;
    vertex->d = time;
    visited[index] = true;
    Node *prev = NULL;
    Node *temp = vertex;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
        if (visited[temp->index] == false)
        {
            temp = this->toUse.A[temp->index];
            DFS_run(temp, temp->index);
            temp = prev;
        }
    }
    time = time + 1;
    vertex->f = time;
}

void DFS ::DFS2(Graph G, Node *vertex)
{
    visited[vertex->index] = true;
    Node *temp = vertex;
    Node *prev = NULL;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
        if (visited[temp->index] == false)
        {
            temp = G.A[temp->index];
            DFS2(G, temp);
            temp = prev;
            sccSize++;
        }
    }
}

void DFS ::scc()
{
    int scc = 0;
    for (int i = 0; i < numVertices; i++)
    {
        if (visited[i] == false)
        {
            DFS_run(this->toUse.A[i], i);
        }
    }
    Graph G_T = toUse.getTranspose();
    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = false;
        G_T.A[i]->d = toUse.A[i]->d;
        G_T.A[i]->f = toUse.A[i]->f;
    }
    // G_T.printADJ();
    int localMax = 0;
    Node **s = G_T.sortAdjancency();
    for (int i = 0; i < numVertices; i++)
    {
        sccSize = 1;
        if (visited[s[i]->index] == false)
        {
            DFS2(G_T, s[i]);
            scc = scc + 1;
            if (sccSize > localMax)
            {
                localMax = sccSize;
            }
        }
    }
    int *arr = new int[localMax];
    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < localMax; i++){
        arr[i] = 0;
    }

    for (int i = 0; i < numVertices; i++)
    {
        sccSize = 1;
        if (visited[s[i]->index] == false)
        {
            DFS2(G_T, s[i]);
            arr[sccSize-1] += 1;
        }
    }
    
    cout << "The graph G has " << scc << " strongly connected components:" << endl;
    cout << "\tSize : Number" << endl;

    for(int i = 0; i < localMax; i++){
        if(arr[i] != 0){
            cout << "\t" << i+1 << " : " << arr[i] << endl;
        }        
    }
}
