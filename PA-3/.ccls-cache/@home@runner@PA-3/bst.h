#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree(){};
    ~BinarySearchTree(){};

    int insertion(int key);
    int deletion(int key);
    int sum(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    Node* _insert(Node* node, int key, int &status);
    Node* _deleteNode(Node* node, int key, int &status);
    Node* _findMin(Node* node);
    int _sumGreater(Node* node, int key);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};