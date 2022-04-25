/*
    Class Name: utiltiy
    Function: Provides Various utility functions like sort
*/

class utility
{
    /*
        Private Member Functions
    */
private:
    void merge(int arr[], int left, int mid, int right);
    void mergeSort(int arr[], int start, int end);

public:
    void sort(int arr[], int size);
    void printArr(int arr[], int size);
    std ::string findTheNthWord(std::string line, int wordPos);
    bool TestForPrime(int val);
};