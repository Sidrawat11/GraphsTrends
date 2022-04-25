/*
 *########################################################
 *########### Including Standard C++ Libraries ###########
 *########################################################
 */
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
/*
 *#############################################################
 *###########  Including Self-Made C++ HeaderFiles ###########
 *#############################################################
 */
#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#include "graph.h"
#endif
#include "utility.h"
#include "FW.h"
#include "DFS.h"
using namespace std;

int main(int argv, char **argc)
{
    utility utilObj;
    int size = 0;

    fstream edgesFile;    // This is the file in the 1st commandline parameter
    fstream datesFile;    // This is the file in the 2nd commandline parameter
    fstream commandsFile; // This is the file in the 3rd commandline parameter

    // Opening all the files for reading
    edgesFile.open(argc[1]);
    datesFile.open(argc[2]);
    commandsFile.open(argc[3]);

    string command;    // This will take in the Commands from the command file
    string vertexInfo; // This will take in the vertexInfo from the dates file
    string edges;      // This will take in the edges info from the edges file

    // Taking in the first command
    getline(commandsFile, command);
    // This will find the range in which we need to start a graph
    int begYear = std::stoi(utilObj.findTheNthWord(command, 1));
    int endYear = std::stoi(utilObj.findTheNthWord(command, 2));

    // Get the size of the to populate the vertex set
    while (getline(datesFile, vertexInfo))
    {
        if (std::stoi(utilObj.findTheNthWord(vertexInfo, 1)) >= begYear && std::stoi(utilObj.findTheNthWord(vertexInfo, 1)) <= endYear)
        {
            size++;
        }
    }

    // Clear the stream and move to the begining: Just in case
    datesFile.clear();
    datesFile.seekg(0, ios::beg);

    // Now creating the populating the Vertex Set
    int *V = new int[size];
    int ctr = 0;
    while (!datesFile.eof() && ctr < size)
    {
        getline(datesFile, vertexInfo);
        if (std::stoi(utilObj.findTheNthWord(vertexInfo, 1)) >= begYear && std::stoi(utilObj.findTheNthWord(vertexInfo, 1)) <= endYear)
        {
            V[ctr] = std::stoi(utilObj.findTheNthWord(vertexInfo, 0));
            ctr++;
        }
    }

    // Now Sort the Array; Used Merge Sort: Time Complexity is O(nlogn)
    utilObj.sort(V, size);

    // Putting Everything into A HashMap
    HashMap map(size);
    for (int i = 0; i < size; i++)
    {
        map.put(V[i], i);
    }

   
    // Now Populate the edges
    int edgeSize = 0;
    while (getline(edgesFile, edges))
    {
        int src = std::stoi(utilObj.findTheNthWord(edges, 0));
        int dest = std::stoi(utilObj.findTheNthWord(edges, 1));
        if (map.keyExist(src) && map.keyExist(dest))
        {
            edgeSize++;
        }
    }

    // Clear the stream and move to the begining: Just in case
    edgesFile.clear();
    edgesFile.seekg(0, ios::beg);

    Pair **E = new Pair*[edgeSize];
    ctr = 0;
    while (getline(edgesFile, edges) && ctr < edgeSize)
    {
        int src = std::stoi(utilObj.findTheNthWord(edges, 0));
        int dest = std::stoi(utilObj.findTheNthWord(edges, 1));
        if (map.keyExist(src) && map.keyExist(dest))
        {
            E[ctr] = new Pair(src, dest);
            ctr++;
        }
    }

    // After Creating the Vertex set We run the commands
    // First make the graph
    Graph G(size, edgeSize, V, E);


    while (!commandsFile.eof())
    {
        command.pop_back();
        cout << "Command: " << command << endl
             << endl;
        if (command.compare("out-degree") == 0)
        {
            float out_degree = (floor((float(edgeSize) / size) * 100)) / 100;
            printf("The graph G has average out-degree %d/%d = %.2f.\n\n", edgeSize, size, out_degree);
            G.outDegree();
        }
        else if (command.compare("diameter") == 0)
        {
            FW algoRun(G, size);
            int diameter = algoRun.floyd_Warshal();
            cout << "The graph G has diameter " << diameter << "." << endl
                 << endl;
        }
        else if (command.compare("scc") == 0)
        {
           DFS algoRun(size, G);
           algoRun.scc();
        }else if(command.compare("end-graph") == 0){
            break;
        }
        else
        {
            cout << "The graph G for the years " << begYear << " " << endYear << " has:" << endl;
            cout << "\t|V| = " << size << " vertices" << endl;
            cout << "\t|E| = " << edgeSize << " edges" << endl
                 << endl;
        }
        // Move onto the nextline
        getline(commandsFile, command);
    }
    return 0;
}
