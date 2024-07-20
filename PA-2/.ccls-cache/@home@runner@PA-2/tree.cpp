#include "tree.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {

  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

void BinaryTree::_printNodeAndChildren(string &list, Node *node) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  if (node == NULL) {
    return;
  }

  // 노드의 값과 자식 노드의 수를 문자열에 추가
  int childrenCount = 0;
  if (node->left != NULL)
    childrenCount++;
  if (node->right != NULL)
    childrenCount++;

  list += node->value;
  list += to_string(childrenCount);

  // 왼쪽과 오른쪽 자식 노드에 대해 재귀적으로 함수 호출
  _printNodeAndChildren(list, node->left);
  _printNodeAndChildren(list, node->right);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::printNodeAndChildren() {
  string list = "";
  _printNodeAndChildren(list, _root);
  return list;
}

int BinaryTree::findHeightOfNode(Node *root, char nodeValue) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int foundHeight = 0;
  bool isFound = false;
  _findHeightOfNode(root, nodeValue, foundHeight, isFound);

  return isFound ? foundHeight : -1;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::findLevelOfNode(Node *root, char nodeValue) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int targetLevel = -1; // 찾고자 하는 노드의 level을 저장할 변수, 초기값은 -1로 설정
  _findLevelOfNode(root, nodeValue, 0, targetLevel); // 재귀적 탐색 시작, 루트 노드의 level은 0
  return targetLevel; // 찾은 노드의 level 반환, 노드를 찾지 못하면 -1 반환
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::levelOrder() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  string result;
  int height = _getHeight(_root);
  for (int i = 1; i <= height; i++) {
      _getLevelOrder(_root, i, result);
  }
  return result;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void BinaryTree::_currentLevel() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::leafCount() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int result = 0;
  result = _leafCount(_root);
  
  return to_string(result);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

const int MAX_DEPTH = 100;
int levels[MAX_DEPTH];

string BinaryTree::getWidth() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  for (int i = 0; i < MAX_DEPTH; ++i) levels[i] = 0;

  _countNodesAtLevel(_root, 0);

  int maxWidth = 0;
  for (int i = 0; i < MAX_DEPTH; ++i) {
      if (levels[i] > maxWidth) maxWidth = levels[i]; // 최대 너비 갱신
  }
  return to_string(maxWidth);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  You can implement any other functions ////////
int BinaryTree::_findHeightOfNode(Node* root, char target, int& foundHeight, bool& isFound) {
    if (!root) return -1; // 노드가 없으면 height는 -1

    int leftHeight = _findHeightOfNode(root->left, target, foundHeight, isFound);
    int rightHeight = _findHeightOfNode(root->right, target, foundHeight, isFound);

    int currentHeight = 1 + max(leftHeight, rightHeight); // 현재 노드의 height 계산

    if (root->value == target) { // 찾고자 하는 노드를 발견했으면
        foundHeight = currentHeight;
        isFound = true;
    }

    return currentHeight; // 현재 노드를 루트로 하는 서브트리의 height 반환
}

int BinaryTree::_findLevelOfNode(Node* node, char targetValue, int currentLevel, int& targetLevel)
{
    if (node == nullptr) {
      return false; // 현재 노드가 nullptr이면, 탐색 실패
    }
    if (node->value == targetValue) {
      targetLevel = currentLevel; // 찾고자 하는 노드를 찾으면, level을 저장하고 true 반환
      return true;
    }
    // 왼쪽 서브트리 또는 오른쪽 서브트리에서 탐색을 계속합니다.
    return _findLevelOfNode(node->left, targetValue, currentLevel + 1, targetLevel) ||
         _findLevelOfNode(node->right, targetValue, currentLevel + 1, targetLevel);
}

int BinaryTree::_getHeight(Node* node) {
  if (node == nullptr) return 0;
  int leftHeight = _getHeight(node->left);
  int rightHeight = _getHeight(node->right);
  return 1 + std::max(leftHeight, rightHeight);
}

void BinaryTree::_getLevelOrder(Node* node, int level, string& result) {
    if (!node) return;
    if (level == 1) {
        result += node->value;
        result += " ";
    } else if (level > 1) {
        _getLevelOrder(node->left, level - 1, result);
        _getLevelOrder(node->right, level - 1, result);
    }
}

int BinaryTree::_leafCount(Node* node)
{
  if (node == nullptr){
    return 0;
  }
  if (node->left == nullptr && node->right == nullptr) {
    return 1; // 현재 노드가 리프 노드이면 1 반환
  }
  // 왼쪽 서브트리와 오른쪽 서브트리에서 재귀적으로 리프 노드의 개수를 세고 합산
  return _leafCount(node->left) + _leafCount(node->right);
}

// 각 레벨의 노드 수를 계산하는 재귀 함수
void BinaryTree::_countNodesAtLevel(Node* node, int level) {
    if (node == nullptr) return; // 기저 조건
    levels[level]++; // 현재 레벨의 노드 수 증가
    _countNodesAtLevel(node->left, level + 1); // 왼쪽 자식 탐색
    _countNodesAtLevel(node->right, level + 1); // 오른쪽 자식 탐색
}
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////