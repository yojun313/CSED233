#pragma once
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;
// Number of vertices in the graph
#define V 26

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph();
  ~Graph(){};

  /////////////////////////////////////////////////////////
  //////  TODO: Add public members if required ///////////

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  string checkCycle();
  string findFurthest(string nodeA);

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addDirectedEdgeWCC(string nodeA, string nodeB);
  string getTopologicalSort();
  string StrongConnectedComponents();
  string WeaklyConnectedComponents();

  int addExcludedEdge(string nodeA, string nodeB);
  int addIncludedEdge(string nodeA, string nodeB);

  string dijkstra(string source, int budget, ofstream &fout);

  int kruskalMST(ofstream &);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  int edge[100][100] = {0};
  int node_num[100] = {-1,};
  int weight[100][100] = {0};
  int exclude[100][100];
  int include[100][100];
  int count = 0;
  int cnt = 0;
  bool exist[100] = {0};

  int directGraph[26][26] = {0,};
  string pa5_answer;
  bool visited[NodeMaxCount];

  bool dfs(int v, int parent);
  void bfs(int start, int dist[], int &maxDist);
  int getNodeIndex(string node);
  void resetVisited();
  void enqueue(int queue[], int &rear, int value);
  int dequeue(int queue[], int &front, int rear);

  void dfsSCC(int v, bool visited[], int stack[], int &stackIndex);
  void dfsTranspose(int v, bool visited[], int component[], int &compIndex);
  void dfsWCC(int v, bool visited[], int component[], int &compIndex);
  void sortComponents(char components[][100], int compSizes[], int compCount);

  void unionSets(int parent[], int rank[], int x, int y);
  int findSet(int parent[], int i);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
