#include "FW.h"
#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#include "graph.h"
#endif

#define INF 999999999

FW ::FW(Graph G, int N){
    this->N = N;
    adjMatrix = new int*[N];
    
    //This is dynamic-memory allocation fro 2D array
    for(int i = 0; i < N; i++){
        adjMatrix[i] = new int[N];
    }

    //Initializing the Diaognal to Zero and rest to INF 
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == j){
                adjMatrix[i][j] = 0;
            }else{
                adjMatrix[i][j] = INF;
            }
        }
    }

    //Goes through each row and set the columns that have an edge to current to 1
    for(int i = 0; i < N; i++){
        Node *temp = G.getNode(i);
        while(temp->next != NULL){
            temp = temp->next;
            int j = temp->index;
            adjMatrix[i][j] = 1;
        } 
    }
}

int FW ::floyd_Warshal(){
    int localMax = -1;
    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                adjMatrix[i][j] = std::min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                if(adjMatrix[i][j] > localMax && adjMatrix[i][j] != INF){
                    localMax = adjMatrix[i][j];
                }
            }
        }
    }
    return localMax;
}
void FW ::printMatrix(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(adjMatrix[i][j] == INF){
                cout << "INF"<< "\t";
            }else{
                cout << adjMatrix[i][j] << "\t";
            }
            
        }
        cout << endl;
    }
}