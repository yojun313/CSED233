#include <iostream>
#include <fstream>
#include <string>
#include "closed_hash_function.h"
#include "closed_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

ClosedHashTable::ClosedHashTable(int table_size, int k, int d1, ClosedHashFunction *hf) : table_size(table_size), k(k), d1(d1)
{
    this->hf = hf;
    this->table = new int[this->table_size];
    this->states = new ClosedTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i)
    {
        this->states[i] = CLOSED_EMPTY;
    }

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */
    this->pseudo_random_sequence = new int[this->table_size - 1];
    this->pseudo_random_sequence[0] = d1;
    int current_value = d1;

    for (int i = 1; i < this->table_size - 1; ++i) {
        current_value = 2 * current_value;
        if (current_value >= this->table_size) {
            current_value -= this->table_size;
            current_value ^= k;
        }
        this->pseudo_random_sequence[i] = current_value;
    }
    
    hf->set_pseudo_random_sequence(this->pseudo_random_sequence, this->table_size - 1);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

ClosedHashTable::~ClosedHashTable()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */
    delete[] this->pseudo_random_sequence;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] this->table;
    delete[] this->states;
}

void ClosedHashTable::print_table(ostream &out)
{
    for (int i = 0; i < this->table_size; i++)
    {
        out << i << ": ";
        if (this->states[i] == CLOSED_EMPTY)
            out << "EMPTY" << endl;
        else if (this->states[i] == CLOSED_OCCUPIED)
            out << this->table[i] << endl;
        else
            out << "UNKNOWN" << endl;
    }
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */
    if (success == false) out << "FAIL" << endl;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void ClosedHashTable::insert(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int attempt = 0;
    int index;

    index = hf->closedhashing1(key);

    if (success == true) {
        if (this->states[index] == CLOSED_EMPTY) {
            this->table[index] = key;
            this->states[index] = CLOSED_OCCUPIED;
            return;
        }
        else {
            while (attempt < this->table_size - 1) {
                // pseudo_random_sequence를 활용한 최종 인덱스 계산
                index = hf->closedhashing(key, attempt);

                if (this->states[index] == CLOSED_EMPTY) {
                    this->table[index] = key;
                    this->states[index] = CLOSED_OCCUPIED;
                    return;
                }
                attempt++;
            }
        }
    }
    success = false;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
