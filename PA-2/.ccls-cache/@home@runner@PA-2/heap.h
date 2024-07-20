#pragma once
#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 100

struct pq_element
{
    int priority;
    int value;
};

class PriorityQueue
{
private:
    pq_element heap[MAX_SIZE];
    int size;
    /* BEGIN_YOUR_CODE */
    void bubbleUp(int index) {
        while (index > 0) {
            int parentIdx = (index - 1) / 2;
            if (heap[index].priority > heap[parentIdx].priority) {
                // swap
                pq_element temp = heap[index];
                heap[index] = heap[parentIdx];
                heap[parentIdx] = temp;
  
                index = parentIdx;
            } else {
                break;
            }
        }
    }
    void bubbleDown(int index) {
        int leftChildIdx, rightChildIdx, largestIdx;
        while (index < size) {
            leftChildIdx = 2 * index + 1;
            rightChildIdx = 2 * index + 2;
            largestIdx = index;

            if (leftChildIdx < size && heap[leftChildIdx].priority > heap[largestIdx].priority) {
                largestIdx = leftChildIdx;
            }

            if (rightChildIdx < size && heap[rightChildIdx].priority > heap[largestIdx].priority) {
                largestIdx = rightChildIdx;
            }

            if (largestIdx != index) {
                // swap
                pq_element temp = heap[index];
                heap[index] = heap[largestIdx];
                heap[largestIdx] = temp;
                index = largestIdx;
            } else {
                break;
            }
        }
    }
    /* END_YOUR_CODE */

public:
    PriorityQueue()
    {
        size = 0;
    }

    bool insert(int priority, int value); // insert element

    bool removeMax(); // remove a pq_element having maximum priority

    pq_element getMax(); // return a pq_element having maximum priority

    bool empty(); // is it empty?

    string printPQ();

    bool changeMax(int target);
};