#ifndef DEFNS
#define DEFNS
#include "defns.h"
#include "HashMap.h"
#endif
#include "graph.h" 

Graph ::Graph(){}
Graph ::Graph(int size, int e_size, int arr[], Pair **eSet)
{
    A = new Node *[size];
    E = new Pair *[e_size];
    V = new int [size];
    this->size = size;
    this->edges_size = e_size;
    for (int i = 0; i < size; i++)
    {
        A[i] = NULL;
    }

    HashMap vertexSet(size);
    for (int i = 0; i < size; i++)
    {
        A[i] = new Node(arr[i], i);
        vertexSet.put(arr[i], i);
        V[i] = arr[i];
    }

    for(int i = 0; i < e_size; i++){
        E[i] = new Pair(eSet[i]->src, eSet[i]->dest);
        int srcIndex = vertexSet.findKey(eSet[i]->src);
        int destIndex = vertexSet.findKey(eSet[i]->dest);
        addEdge(srcIndex, destIndex);
    }

}

void Graph ::addEdge(int src, int dest)
{
    Node *currentVertex = A[src];
    Node *temp = new Node(A[dest]->val, A[dest]->index);
    // Node *prev = NULL;
    // If there is a chain traverse it
    while (currentVertex->next != NULL)
    {
        // prev = currentVertex;
        currentVertex = currentVertex->next;
    }

    currentVertex->next = temp;
}

void Graph ::printADJ()
{
    for (int i = 0; i < size; i++)
    {
        Node *curr = A[i];
        while (curr != NULL)
        {
            if (curr->next == NULL)
            {
                std ::cout << "(Index: " << curr->index << ", " << curr->d << "," << curr->f << ")" << std ::endl;
            }
            else
            {
                std ::cout << "(Index: " << curr->index << ", "  << curr->d << "," << curr->f << ") ---->";
            }
            curr = curr->next;
        }
    }
}

void Graph ::outDegree()
{
    int max = -1;
    for (int i = 0; i < size; i++)
    {
        Node *temp = A[i];
        int listCount = 0;
        if (temp->next != NULL)
        {
            while (temp->next != NULL)
            {
                listCount++;
                temp = temp->next;
            }
            if (listCount > max)
            {
                max = listCount;
            }
        }
    }

    cout << "The out-degree distribution is:" << endl;
    cout << "\tOut-degree : Number of vertices" << endl;

    int j = 0;
    while (j <= max)
    {
        int localCount = 0;
        for (int i = 0; i < size; i++)
        {
            Node *temp = A[i];
            int listCount = 0;
            if (temp->next != NULL)
            {
                while (temp->next != NULL)
                {
                    listCount++;
                    temp = temp->next;
                }
                if (listCount == j)
                {
                    localCount++;
                }
            }
            else
            {
                if (j == 0)
                {
                    localCount++;
                }
            }
        }
        if (localCount != 0)
        {
            cout << "\t" << j << " : " << localCount << endl;
        }
        j++;
    }

    cout << endl;
}

Node* Graph ::getNode(int index){
    return A[index];
}

Graph Graph ::getTranspose(){
    Pair **temp = new Pair *[edges_size];
    for(int i = 0; i < edges_size; i++){
        temp[i] = new Pair(E[i]->dest, E[i]->src);
    }

    Graph gt(size, edges_size, V, temp);
    return gt;

}

Node** Graph ::sortAdjancency(){
    Node **temp = new Node*[size];
    for(int i = 0; i < size; i++)
        temp[i] = A[i];
    mergeSort(temp, 0, size-1);
    return temp;
}

void Graph ::mergeSort(Node **arr, int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    mergeList(arr, start, mid, end);
}

void Graph::mergeList(Node **arr, int left, int mid, int right)
{

    /* Creating two SUB_Array */
    int arr_left = mid - left + 1;
    int arr_right = right - mid;

    Node **leftArr = new Node*[arr_left];
    Node **rightArr = new Node*[arr_right];

    // Copying the contents of array in the respective subarray
    for (int i = 0; i < arr_left; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < arr_right; j++)
    {
        rightArr[j] = arr[mid + 1 + j];
    }

    int indexLeft = 0, indexRight = 0, indexMain = left;

    // Merge the temp arrays back into array[left..right]
    while (indexLeft < arr_left && indexRight < arr_right)
    {
        if (leftArr[indexLeft]->f >= rightArr[indexRight]->f)
        {
            arr[indexMain] = leftArr[indexLeft];
            indexLeft++;
        }
        else
        {
            arr[indexMain] = rightArr[indexRight];
            indexRight++;
        }
        indexMain++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexLeft < arr_left)
    {
        arr[indexMain] = leftArr[indexLeft];
        indexLeft++;
        indexMain++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexRight < arr_right)
    {
        arr[indexMain] = rightArr[indexRight];
        indexRight++;
        indexMain++;
    }
}