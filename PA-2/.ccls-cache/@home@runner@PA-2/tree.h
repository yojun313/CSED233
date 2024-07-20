#pragma once
#include <fstream>
#include <string>
using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  Node *getRoot() { return _root; }

  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  int findHeightOfNode(Node *root, char nodeValue);
  int findLevelOfNode(Node *root, char nodeValue);

  string levelOrder();
  string printNodeAndChildren();

  string leafCount();
  string getWidth();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  void _printNodeAndChildren(string &list, Node *node);
  void _currentLevel();
  int _findHeightOfNode(Node* root, char target, int& foundHeight, bool& isFound);
  int _findLevelOfNode(Node* root, char targetValue, int currentLevel, int& targetLevel);
  int _getHeight(Node* node);
  void _getLevelOrder(Node* node, int level, std::string& result);
  int _leafCount(Node* node);
  void _countNodesAtLevel(Node* node, int level);

  static const int MAX_DEPTH = 100;
  int levelCounts[MAX_DEPTH] = {0};

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};