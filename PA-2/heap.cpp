#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

string PriorityQueue::printPQ()
{
    string answer;
    for (int i = 0; i < size; i++)
        answer += to_string(heap[i].value) + " ";
    return answer;
}

bool PriorityQueue::insert(int priority, int value)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (size >= 100) {
      return 0;
    }
    pq_element element;
    element.priority = priority;
    element.value = value;
    heap[size] = element;
    bubbleUp(size);
    size++;
  
    return 1;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::removeMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (size == 0) {
      return 0;
    }
    heap[0] = heap[size - 1];
    size--;
    bubbleDown(0);

    return 1;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

pq_element PriorityQueue::getMax()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return heap[0];
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::empty()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (size == 0) return true;
    else return false;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool PriorityQueue::changeMax(int target)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int maxPriority = getMax().value;
    bool found = false;

    for (int i = 0; i < size; ++i) {
        if (heap[i].priority == target) {
            heap[i].priority = maxPriority + 1; // Update the priority
            heap[i].value = maxPriority + 1;
            bubbleUp(i);
            found = true;
            break; // Assuming the first matching priority
        }
    }
    return found;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
