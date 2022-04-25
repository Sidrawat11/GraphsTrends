#include <iostream>
using namespace std;

/*
####################################################################
########### Provides Definations of Necessary Structures ###########
####################################################################
*/

struct Pair
{
    int src, dest;
    Pair(int src,int dest){
        this->src =src;
        this->dest = dest;
    }
};

struct HashTableEntry{
    int key, value;
    HashTableEntry *next;
    HashTableEntry(int key, int value){
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

struct Node{
    int val,index;
    int d, f;
    Node *next;
    Node(int val, int index){
        this->index = index;
        this->val = val;
        this->next = NULL;
    }
};