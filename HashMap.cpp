/*
########################################################################################################
########### Following is the definition of class functions (HashTable by Sepereate Chaining) ###########
########################################################################################################
*/
#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include "utility.h"
#include "HashMap.h"

HashMap ::HashMap(int size)
{
    utility obj;
    int s = 3*size;
    while (!obj.TestForPrime(s))
    {
        s++;
    }
    buckets = s;
    map = new HashTableEntry *[buckets];
    for (int i = 0; i < buckets; i++)
    {
        map[i] = NULL;
    }
}

int HashMap ::hash(int key){
    return key % buckets;
}

//Here Key is the Vertex while the value is the is the index!!
void HashMap ::put(int key, int value){
    int pos = hash(key);
    HashTableEntry *currentEntry= NULL;
    HashTableEntry *newEntry = map[pos];

    //If there is a chain this will traverse at the end of that chain
    while(newEntry != NULL){
        currentEntry = newEntry;
        newEntry = newEntry->next;
    }

    //If the newEntry position is null 
    //It will create a new HashtableEntry with the key = vertex and the value = index
    if(newEntry == NULL){
        newEntry = new HashTableEntry(key, value);

        //If currentEntry is NULL set the HashTable at the position to new entry
        //Else put the new entry to next of the CurrentEntry
        if(currentEntry == NULL){
            map[pos] = newEntry;
        }else{
            currentEntry->next = newEntry;
        }
    }else{
        newEntry->value = value;
    }
}

int HashMap ::findKey(int key){
    int key_pos = hash(key);
    HashTableEntry *curr = map[key_pos];
    while(curr != NULL){
        if(curr->key == key){
            return curr->value;
        }else{
            curr = curr->next;
        }
    } 
    return -1;
}

bool HashMap ::keyExist(int key){
    int key_pos = hash(key);
    HashTableEntry *curr = map[key_pos];
    while(curr != NULL){
        if(curr->key == key){
            return true;
        }else{
            curr = curr->next;
        }
    } 
    return false;
}