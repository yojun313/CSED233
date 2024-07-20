#include <iostream>
#include <fstream>
#include <string>
#include "open_hash_function.h"
#include "open_hash_table.h"

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

OpenHashTable::OpenHashTable(int table_size, OpenHashFunction *hf) : table_size(table_size)
{
    this->hf = hf;
    this->collision = 0;
    this->longest = 0;
    table = new HashNode *[this->table_size];
    for (int i = 0; i < this->table_size; i++)
    {
        table[i] = NULL;
    }
    this->states = new OpenTableState[this->table_size];

    for (int i = 0; i < this->table_size; ++i)
    {
        this->states[i] = OPEN_EMPTY;
    }

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

OpenHashTable::~OpenHashTable()
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */

    for (int i = 0; i < table_size; i++) {
      HashNode* node = table[i];
      while (node != nullptr) {
          HashNode* temp = node;
          node = node->next;
          delete temp;
      }
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    delete[] table;
    delete[] this->states;
}

void OpenHashTable::print_result(ostream &out)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    /*  Write your codes if you need  */
    

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    out << collision << " " << longest << endl;
}

void OpenHashTable::insert(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int index = hf->openhashing(key);
    HashNode* newNode = new HashNode(key);
    if (table[index] != nullptr) {
        collision++;  // 충돌 발생
    } else {
        states[index] = OPEN_OCCUPIED;
    }
    newNode->next = table[index];
    table[index] = newNode;

    // 가장 긴 체인 업데이트
    int chainLength = 0;
    HashNode* temp = table[index];
    while (temp != nullptr) {
        chainLength++;
        temp = temp->next;
    }
    if (chainLength > longest) {
        longest = chainLength;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

void OpenHashTable::delete_(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int index = hf->openhashing(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;
  
    bool found = false;
    while (current != nullptr) {
        if (current->key == key) {
            found = true;
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }
  
    if (found) {
        // 가장 긴 체인 길이 재계산
        int chainLength = 0;
        current = table[index];
        while (current != nullptr) {
            chainLength++;
            current = current->next;
        }
  
        // 필요한 경우 최대 체인 길이 업데이트
        if (chainLength < longest) {
            int newLongest = 0;
            for (int i = 0; i < table_size; i++) {
                int localLength = 0;
                current = table[i];
                while (current != nullptr) {
                    localLength++;
                    current = current->next;
                }
                if (localLength > newLongest) {
                    newLongest = localLength;
                }
            }
            longest = newLongest;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
