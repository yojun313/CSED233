#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
Node* BinarySearchTree::_insert(Node* node, int key, int &status) {
    if (!node) return new Node(key);

    if (key == node->key) {
        status = -1; // Key already exists
    } else if (key < node->key) {
        node->left = _insert(node->left, key, status);
    } else {
        node->right = _insert(node->right, key, status);
    }
    return node;
}

Node* BinarySearchTree::_deleteNode(Node* node, int key, int &status) {
    if (!node) {
        status = -1;
        return nullptr;
    }
    if (key < node->key) {
        node->left = _deleteNode(node->left, key, status);
    } else if (key > node->key) {
        node->right = _deleteNode(node->right, key, status);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            Node* temp = _findMin(node->right);
            node->key = temp->key;
            node->right = _deleteNode(node->right, temp->key, status);
        }
    }
    return node;
}

Node* BinarySearchTree::_findMin(Node* node) {
    while (node && node->left) node = node->left;
    return node;
}

int BinarySearchTree::_sumGreater(Node* node, int key) {
    if (!node) return 0;
    int sum = 0;
    if (node->key > key) {
        sum += node->key;
    }
    sum += _sumGreater(node->left, key);
    sum += _sumGreater(node->right, key);
    return sum;
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int BinarySearchTree::insertion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int status = 0;
    _root = _insert(_root, key, status);
    return status;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int status = 0;
    _root = _deleteNode(_root, key, status);
    return status;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BinarySearchTree::sum(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    return _sumGreater(_root, key);
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}