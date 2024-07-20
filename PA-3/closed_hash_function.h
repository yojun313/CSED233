#pragma once
#include <iostream>
#include <string>
using namespace std;

class ClosedHashFunction
{

public:
    ClosedHashFunction(int m) : index_size(m), pseudo_random_sequence(nullptr) {};

    ~ClosedHashFunction() {
        delete[] pseudo_random_sequence;
    }

    int closedhashing(int key, int attempt);
    int closedhashing1(int key);
    int closedhashing2(int attempt);
    /////////////////////////////////////////////////////////
    //////  TODO: Add public members if required ///////////
    void set_pseudo_random_sequence(int *sequence, int size);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
private:
    int key_size;
    int index_size;
    int *pseudo_random_sequence;
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
