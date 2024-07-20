#include <iostream>

struct pq_element {
    int priority;
    int value;
};

class PriorityQueue {
private:
    pq_element heap[100]; // 고정 크기 배열
    int size;

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

public:
    PriorityQueue() : size(0) {}

    void insert(int priority, int value) {
        if (size >= 100) {
            std::cout << "ERROR: Queue is full." << std::endl;
            return;
        }
        pq_element element;
        element.priority = priority;
        element.value = value; // In this context, value is the same as priority but we store it anyway
        heap[size] = element;
        bubbleUp(size);
        size++;
    }

    void printHeap() {
        for (int i = 0; i < size; ++i) {
            std::cout << heap[i].priority << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    PriorityQueue pq;
    pq.insert(4, 4);
    pq.insert(-2, -2);
    pq.insert(9, 9);
    pq.insert(10, 10);
    pq.insert(15, 15);
    pq.insert(-25, -25);

    pq.printHeap();
    return 0;
}