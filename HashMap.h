#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif

class HashMap
{
    int buckets;
    int hash(int k);

public:
    HashTableEntry **map;
    HashMap(int size);    
    void put(int key, int value);
    int findKey(int key);    
    bool keyExist(int key);
};