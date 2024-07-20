#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg()
{
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout)
{
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}

void sortAlg::bubbleSort(ofstream &fout)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int size = arr_size;
    for (int i = 0; i < size; i++) 
    {
        bool swapped = false;  
        for (int j = size - 1; j > i; j--) {
            if (arr[j - 1] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;  
        printArray(fout);
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int middle, int right, bool &changed)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int *L = new int[n1];
    int *R = new int[n2];
  
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
  
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }
  
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
  
    delete[] L;
    delete[] R;
    changed = true;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int n = arr_size;
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int right = min(i + 2 * width - 1, n - 1);
            int middle = min(i + width - 1, n - 1);
            bool changed = false;
            merge(left, middle, right, changed);
        }
        printArray(fout);
    }
      ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
