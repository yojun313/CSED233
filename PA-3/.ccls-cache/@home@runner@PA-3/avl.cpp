#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

AVLTree::AVLTree()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  
  /*  Write your codes if you need  */
  root = nullptr;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

AVLTree::~AVLTree()
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  /*  Write your codes if you need  */
  _clear(root);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void AVLTree::insert(char letter)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int status = 0;
  int asciiValue = static_cast<int>(letter);
  root = _insert(root, asciiValue, status);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::remove(char letter)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int dummy = 0;
  root = _remove(root, letter, dummy);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void AVLTree::printInOrder(ofstream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  _printInOrder(fout, root);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void AVLTree::printPreOrder(ofstream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  _printPreOrder(fout, root);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
void AVLTree::printFrequency(ofstream &fout)
{
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int nodeCount = _countNodes(root);
  if (nodeCount == 1) {
      fout << "(" << char(root->key) << ", " << root->frequency << ") ";
  }
  else _printFrequency(fout, root, nodeCount);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */
Node* AVLTree::_insert(Node* node, int asciiValue, int &status) {
    if (!node) {
      node = new Node(asciiValue);
      node->frequency = 1;
      node->height = 1;  // 새로 삽입된 노드의 초기 높이는 1
      return node;
    }
  
    if (asciiValue < node->key) {
      node->left = _insert(node->left, asciiValue, status);
    } else if (asciiValue > node->key) {
      node->right = _insert(node->right, asciiValue, status);
    } else {
      node->frequency++;
      return node;
    }
  
    _updateHeight(node);  // 높이 업데이트
    return _balance(node);  // 균형 잡기
}

Node* AVLTree::_remove(Node* node, char key, int &status) {
    if (!node) return nullptr;
  
    if (key < node->key)
        node->left = _remove(node->left, key, status);
    else if (key > node->key)
        node->right = _remove(node->right, key, status);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            node = temp;
        } else {
            Node* temp = _findMin(node->right);
            node->key = temp->key;
            node->frequency = temp->frequency;
            node->right = _remove(node->right, temp->key, status);
        }
    }
  
    return node ? _balance(node) : nullptr;
}

Node* AVLTree::_findMin(Node* node) {
    if (node == nullptr) return nullptr;
    Node* current = node;
    // 가장 왼쪽 노드로 계속 이동합니다.
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Helper functions to get the height of the node
int AVLTree::_height(Node* node) {
    if (!node) return 0;
    return node->height;
}

// Helper function to update the height of the node
void AVLTree::_updateHeight(Node* node) {
    node->height = 1 + max(_height(node->left), _height(node->right));
}

// Right rotation
Node* AVLTree::_rotateRight(Node* y) {
    if (!y || !y->left) return y;  // 추가된 널 체크
    
      Node* x = y->left;
      Node* T2 = x->right;
  
      // Perform rotation
      x->right = y;
      y->left = T2;
  
      // Update heights
      _updateHeight(y);
      _updateHeight(x);
  
      return x;
}

// Left rotation
Node* AVLTree::_rotateLeft(Node* x) {
      if (!x || !x->right) return x;  // 추가된 널 체크
    
      Node* y = x->right;
      Node* T2 = y->left;
    
      // Perform rotation
      y->left = x;
      x->right = T2;
    
      // Update heights
      _updateHeight(x);
      _updateHeight(y);
    
      return y;
}

// Get Balance factor of node N
int AVLTree::_getBalance(Node* node) {
    if (!node) return 0;
    return _height(node->left) - _height(node->right);
}

// Balance the node
Node* AVLTree::_balance(Node* node) {
    if (!node) return node;
  
    _updateHeight(node);
    int balance = _getBalance(node);
  
    // Left Left Case
    if (balance > 1 && _getBalance(node->left) >= 0) {
        return _rotateRight(node);
    }
  
    // Left Right Case
    if (balance > 1 && _getBalance(node->left) < 0) {
        node->left = _rotateLeft(node->left);
        return _rotateRight(node);
    }
  
    // Right Right Case
    if (balance < -1 && _getBalance(node->right) <= 0) {
        return _rotateLeft(node);
    }
  
    // Right Left Case
    if (balance < -1 && _getBalance(node->right) > 0) {
        node->right = _rotateRight(node->right);
        return _rotateLeft(node);
    }
  
    return node;  // 이미 균형이 맞는 경우
}

void AVLTree::_clear(Node* node) {
    if (!node) return;
    _clear(node->left);
    _clear(node->right);
    delete node;
}

void AVLTree::_printInOrder(std::ofstream& fout, Node* node) {
    if (!node) return;  // 널 체크 추가
    _printInOrder(fout, node->left);
    fout << "(" << char(node->key) << ", " << node->frequency << ") ";
    _printInOrder(fout, node->right);
}

void AVLTree::_printPreOrder(std::ofstream& fout, Node* node) {
    if (!node) return;  // 널 체크 추가
    fout << "(" << char(node->key) << ", " << node->frequency << ") ";
    _printPreOrder(fout, node->left);
    _printPreOrder(fout, node->right);
}

void AVLTree::_printFrequency(std::ofstream& fout, Node* node, int size)
{
    Node* sortedNodes[size];
    int index = 0;
    _collectAndSortNodes(root, sortedNodes, index, 100);
  
    for (int i = 0; i < index; i++) 
    {
      if (sortedNodes[i]) {
          fout << "(" << char(sortedNodes[i]->key) << ", " << sortedNodes[i]->frequency << ") ";
      }
    }
}

void AVLTree::_collectAndSortNodes(Node* node, Node* sortedNodes[], int& index, int maxSize) 
{
    if (!node) return;

    // 현재 노드를 삽입 정렬을 사용하여 적절한 위치에 추가
    int pos;
    for (pos = index - 1; pos >= 0; pos--) {
        if (sortedNodes[pos]->frequency < node->frequency ||
            (sortedNodes[pos]->frequency == node->frequency && sortedNodes[pos]->key > node->key)) {
            if (pos + 1 < maxSize) {
                sortedNodes[pos + 1] = sortedNodes[pos];
            }
        } else {
            break;
        }
    }
    if (pos + 1 < maxSize) {
        sortedNodes[pos + 1] = node;
    }
    index++;

    // 왼쪽과 오른쪽 자식 노드도 같은 방식으로 처리
    _collectAndSortNodes(node->left, sortedNodes, index, maxSize);
    _collectAndSortNodes(node->right, sortedNodes, index, maxSize);
}

int AVLTree::_countNodes(Node* node) {
    if (!node) return 0;
    return 1 + _countNodes(node->left) + _countNodes(node->right);
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////