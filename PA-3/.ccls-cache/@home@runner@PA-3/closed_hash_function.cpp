#include "closed_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
void ClosedHashFunction::set_pseudo_random_sequence(int *sequence, int size) {
    delete[] pseudo_random_sequence;
    pseudo_random_sequence = new int[size];
    for (int i = 0; i < size; ++i) {
        pseudo_random_sequence[i] = sequence[i];
    }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int ClosedHashFunction::closedhashing(int key, int attempt)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int base_index = closedhashing1(key);
    int offset = closedhashing2(attempt);

    return (base_index + offset) % index_size;
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing1(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int sum = 0; 
    while (key > 0) {
        sum += key % 10;  
        key /= 10;        
    }
    return sum % index_size;  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int ClosedHashFunction::closedhashing2(int attempt)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (pseudo_random_sequence && attempt < index_size - 1) {
        return pseudo_random_sequence[attempt];
    }
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
