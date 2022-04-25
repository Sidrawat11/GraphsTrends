#include <iostream>
#include "utility.h"
#include <math.h>
using namespace std;

void utility ::sort(int arr[], int size)
{
    mergeSort(arr, 0, size - 1);
}

void utility ::mergeSort(int arr[], int start, int end)
{
    if (start >= end)
        return;

    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

void utility ::merge(int arr[], int left, int mid, int right)
{

    /* Creating two SUB_Array */
    int arr_left = mid - left + 1;
    int arr_right = right - mid;

    int leftArr[arr_left];
    int rightArr[arr_right];

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
        if (leftArr[indexLeft] <= rightArr[indexRight])
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

void utility ::printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i != size - 1)
        {
            cout << arr[i] << " -> ";
        }
        else
        {
            cout << arr[i];
        }
    }
}

bool utility ::TestForPrime(int val)
{
    int limit, factor = 2;
    limit = (long)(sqrtf((float)val) + 0.5f);
    while ((factor <= limit) && (val % factor))
        factor++;
    return (factor > limit);
}

// Returns the word at nth position in the string; Enter n-1 to get word at nth position
string utility ::findTheNthWord(std::string line, int wordPos)
{
    std::string returnVal = "";
    int n = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) == ' ' || line.at(i) == '\t')
        {
            if (n == wordPos)
                break;
            else
            {
                returnVal = "";
                n++;
            }
        }
        else
        {
            returnVal += line.at(i);
        }
    }
    return returnVal;
}