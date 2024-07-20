#pragma once
#include "bst.h"

using namespace std;

class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void insert(char letter);
    void remove(char letter);

    void printInOrder(ofstream &fout);
    void printPreOrder(ofstream &fout);
    void printFrequency(ofstream &fout);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    Node* root;

    Node* _insert(Node* node, int asciiValue, int &status); //
    Node* _remove(Node* node, char key, int &status); //
    Node* _findMin(Node* node); //
    void _clear(Node* node);
    int _height(Node* node); //
    void _updateHeight(Node* node); //
    Node* _rotateRight(Node* node); //
    Node* _rotateLeft(Node* node); //
    int _getBalance(Node* node); //
    Node* _balance(Node* node); //
    void _printInOrder(std::ofstream &fout, Node* node);
    void _printPreOrder(std::ofstream &fout, Node* node);
    void _printFrequency(std::ofstream &fout, Node* node, int size);
    void _collectAndSortNodes(Node* node, Node* sortedNodes[], int& index, int maxSize);
    int _countNodes(Node* node);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};