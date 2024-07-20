#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;
#include <algorithm>

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */
Graph::Graph() {
  for (int i = 0; i < NodeMaxCount - 1; ++i) {
    node_num[i] = -1;
    visited[i] = false;
    for (int j = 0; j < NodeMaxCount - 1; ++j) {
      edge[i][j] = 0;
      weight[i][j] = 0;
      exclude[i][j] = 0;
      include[i][j] = 0;
    }
  }
}

int Graph::getNodeIndex(string node) {
  int index = node[0] - 'A';
  if (node_num[index] == -1) {
    node_num[index] = count++;
  }
  return index;
}

bool Graph::dfs(int v, int parent) {
  visited[v] = true;

  for (int u = 0; u < NodeMaxCount - 1; ++u) {
    if (edge[v][u] == 1) {
      if (!visited[u]) {
        if (dfs(u, v)) {
          return true;
        }
      } else if (u != parent) {
        return true;
      }
    }
  }
  return false;
}

void Graph::bfs(int start, int dist[], int &maxDist) {
  int queue[NodeMaxCount];
  int front = 0, rear = 0;

  for (int i = 0; i < NodeMaxCount - 1; ++i) {
    dist[i] = -1;
  }

  dist[start] = 0;
  queue[rear++] = start;

  while (front < rear) {
    int v = queue[front++];
    for (int u = 0; u < NodeMaxCount - 1; ++u) {
      if (edge[v][u] == 1 && dist[u] == -1) {
        dist[u] = dist[v] + 1;
        queue[rear++] = u;
        if (dist[u] > maxDist) {
          maxDist = dist[u];
        }
      }
    }
  }
}

void Graph::resetVisited() {
  for (int i = 0; i < NodeMaxCount - 1; ++i) {
    visited[i] = false;
  }
}

void Graph::enqueue(int queue[], int &rear, int value) {
  queue[rear++] = value;
}

int Graph::dequeue(int queue[], int &front, int rear) {
  if (front == rear)
    return -1;
  return queue[front++];
}

void Graph::dfsSCC(int v, bool visited[], int stack[], int &stackIndex) {
  visited[v] = true;
  for (int u = 0; u < 100; ++u) {
    if (edge[v][u] == 1 && !visited[u]) {
      dfsSCC(u, visited, stack, stackIndex);
    }
  }
  stack[stackIndex++] = v;
}

void Graph::dfsTranspose(int v, bool visited[], int component[],
                         int &compIndex) {
  visited[v] = true;
  component[compIndex++] = v;
  for (int u = 0; u < 100; ++u) {
    if (edge[u][v] == 1 && !visited[u]) {
      dfsTranspose(u, visited, component, compIndex);
    }
  }
}

void Graph::dfsWCC(int v, bool visited[], int component[], int &compIndex) {
  visited[v] = true;
  component[compIndex++] = v;
  for (int u = 0; u < 100; ++u) {
    if ((edge[v][u] == 1 || edge[u][v] == 1) && !visited[u]) {
      dfsWCC(u, visited, component, compIndex);
    }
  }
}

void Graph::sortComponents(char components[][100], int compSizes[],
                           int compCount) {
  for (int i = 0; i < compCount - 1; ++i) {
    for (int j = i + 1; j < compCount; ++j) {
      bool swap = false;
      for (int k = 0;
           k < 100 && components[i][k] != '\0' && components[j][k] != '\0';
           ++k) {
        if (components[i][k] > components[j][k]) {
          swap = true;
          break;
        } else if (components[i][k] < components[j][k]) {
          break;
        }
      }
      if (swap) {
        for (int k = 0; k < 100; ++k) {
          char temp = components[i][k];
          components[i][k] = components[j][k];
          components[j][k] = temp;
        }
        int tempSize = compSizes[i];
        compSizes[i] = compSizes[j];
        compSizes[j] = tempSize;
      }
    }
  }
}

int Graph::findSet(int parent[], int i) {
  if (parent[i] != i) {
    parent[i] = findSet(parent, parent[i]);
  }
  return parent[i];
}

void Graph::unionSets(int parent[], int rank[], int u, int v) {
  int rootU = findSet(parent, u);
  int rootV = findSet(parent, v);
  if (rank[rootU] < rank[rootV]) {
    parent[rootU] = rootV;
  } else if (rank[rootU] > rank[rootV]) {
    parent[rootV] = rootU;
  } else {
    parent[rootV] = rootU;
    rank[rootU]++;
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

/////////1,2

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  edge[indexA][indexB] = 1;
  edge[indexB][indexA] = 1;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  edge[indexA][indexB] = 1;
  edge[indexB][indexA] = 1;
  this->weight[indexA][indexB] = weight;
  this->weight[indexB][indexA] = weight;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addExcludedEdge(string nodeA, string nodeB) {
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  exclude[indexA][indexB] = 1;
  exclude[indexB][indexA] = 1;
  return 0;
}

int Graph::addIncludedEdge(string nodeA, string nodeB) {
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  include[indexA][indexB] = 1;
  include[indexB][indexA] = 1;
  return 0;
}

string Graph::checkCycle() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  resetVisited();

  for (int v = 0; v < 26; ++v) {
    if (node_num[v] != -1 && !visited[v]) {
      if (dfs(v, -1)) {
        return "TRUE";
      }
    }
  }
  return "FALSE";
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::findFurthest(string nodeA) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int start = getNodeIndex(nodeA);
  int dist[NodeMaxCount];
  int maxDist = 0;

  bfs(start, dist, maxDist);

  string result = "";
  for (int i = 0; i < NodeMaxCount; ++i) {
    if (dist[i] == maxDist) {
      char node = 'A' + i;
      if (!result.empty()) {
        result += "\n";
      }
      result += node;
    }
  }
  result += "\n";
  result += to_string(maxDist);
  return result;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  if (edge[indexA][indexB] == 0) {
    edge[indexA][indexB] = 1;
  }
  return 0;
}

int Graph::addDirectedEdgeWCC(string nodeA, string nodeB) {
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  if (edge[indexA][indexB] == 0) {
    edge[indexA][indexB] = 1;
  }
  return 0;
}

string Graph::getTopologicalSort() {
  int in_degree[NodeMaxCount] = {0};

  for (int i = 0; i < 100; ++i) {
    if (node_num[i] != -1) {
      for (int j = 0; j < 100; ++j) {
        if (edge[i][j] == 1) {
          in_degree[j]++;
        }
      }
    }
  }

  int queue[NodeMaxCount];
  int front = 0, rear = 0;

  for (int i = 0; i < 100; ++i) {
    if (node_num[i] != -1 && in_degree[i] == 0) {
      enqueue(queue, rear, i);
    }
  }

  sort(queue + front, queue + rear);

  int topological_order[100];
  int order_index = 0;

  while (front < rear) {
    int v = dequeue(queue, front, rear);
    topological_order[order_index++] = v;

    for (int u = 0; u < 100; ++u) {
      if (edge[v][u] == 1) {
        in_degree[u]--;
        if (in_degree[u] == 0) {
          enqueue(queue, rear, u);
        }
      }
    }

    sort(queue + front, queue + rear);
  }

  if (order_index != count) {
    return "ERROR";
  }

  string result = "";
  for (int i = 0; i < order_index; ++i) {
    char node = 'A' + topological_order[i];
    result += node;
    if (i != order_index - 1) {
      result += " ";
    }
  }
  return result;
}

string Graph::StrongConnectedComponents() {
  bool visited[100] = {0};
  int stack[100];
  int stackIndex = 0;

  for (int i = 0; i < 100; ++i) {
    if (node_num[i] != -1 && !visited[i]) {
      dfsSCC(i, visited, stack, stackIndex);
    }
  }

  fill(visited, visited + 100, false);
  string result = "";

  char components[100][100];
  int compSizes[100] = {0};
  int compCount = 0;

  while (stackIndex > 0) {
    int v = stack[--stackIndex];
    if (!visited[v]) {
      int component[100];
      int compIndex = 0;
      dfsTranspose(v, visited, component, compIndex);

      sort(component, component + compIndex);

      for (int i = 0; i < compIndex; ++i) {
        components[compCount][i] = (char)('A' + component[i]);
      }
      components[compCount][compIndex] = '\0';
      compSizes[compCount] = compIndex;
      compCount++;
    }
  }

  sortComponents(components, compSizes, compCount);

  for (int i = 0; i < compCount; ++i) {
    for (int j = 0; j < compSizes[i]; ++j) {
      result += components[i][j];
      if (j != compSizes[i] - 1) {
        result += " ";
      }
    }
    if (i != compCount - 1) {
      result += "\n";
    }
  }

  return result;
}

string Graph::WeaklyConnectedComponents() {
  bool visited[100] = {0};
  string result = "";

  char components[100][100];
  int compSizes[100] = {0};
  int compCount = 0;

  for (int i = 0; i < 100; ++i) {
    if (node_num[i] != -1 && !visited[i]) {
      int component[100];
      int compIndex = 0;
      dfsWCC(i, visited, component, compIndex);

      for (int x = 0; x < compIndex - 1; ++x) {
        for (int y = x + 1; y < compIndex; ++y) {
          if (component[x] > component[y]) {
            int temp = component[x];
            component[x] = component[y];
            component[y] = temp;
          }
        }
      }

      for (int j = 0; j < compIndex; ++j) {
        components[compCount][j] = (char)('A' + component[j]);
      }
      components[compCount][compIndex] = '\0';
      compSizes[compCount] = compIndex;
      compCount++;
    }
  }

  sortComponents(components, compSizes, compCount);

  for (int i = 0; i < compCount; ++i) {
    for (int j = 0; j < compSizes[i]; ++j) {
      result += components[i][j];
      if (j != compSizes[i] - 1) {
        result += " ";
      }
    }
    if (i != compCount - 1) {
      result += "\n";
    }
  }

  return result;
}

///////////      End of Implementation      /////////////
///////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions for task5  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int indexA = getNodeIndex(nodeA);
  int indexB = getNodeIndex(nodeB);
  edge[indexA][indexB] = 1;
  this->weight[indexA][indexB] = weight;
  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

std::string Graph::dijkstra(std::string source, int budget,
                            std::ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  int dist[NodeMaxCount];
  int parent[NodeMaxCount];
  bool visited[NodeMaxCount] = {0};

  for (int i = 0; i < NodeMaxCount; ++i) {
    dist[i] = INF;
    parent[i] = -1;
  }

  int srcIndex = getNodeIndex(source);
  dist[srcIndex] = 0;

  for (int count = 0; count < NodeMaxCount - 1; ++count) {
    int u = -1;
    for (int i = 0; i < NodeMaxCount; ++i) {
      if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
        u = i;
      }
    }

    if (dist[u] == INF)
      break;

    visited[u] = true;

    for (int v = 0; v < NodeMaxCount - 1; ++v) {
      if (edge[u][v] && !visited[v] && dist[u] + weight[u][v] < dist[v]) {
        dist[v] = dist[u] + weight[u][v];
        parent[v] = u;
      }
    }
  }

  bool anyPath = false;
  for (int i = 0; i < NodeMaxCount; ++i) {
    if (dist[i] <= budget && dist[i] != INF && i != srcIndex) {
      char node = 'A' + i;
      fout << node << " " << dist[i] << "\n";
      anyPath = true;
    }
  }

  if (!anyPath) {
    fout << "\n";
    return "";
  }

  int maxNodes = 0;
  int maxNodeIndex = -1;
  for (int i = 0; i < NodeMaxCount; ++i) {
    if (dist[i] <= budget && dist[i] != INF && i != srcIndex) {
      int countNodes = 0;
      for (int v = i; v != -1; v = parent[v]) {
        countNodes++;
      }
      if (countNodes > maxNodes) {
        maxNodes = countNodes;
        maxNodeIndex = i;
      }
    }
  }

  if (maxNodeIndex != -1) {
    int path[NodeMaxCount];
    int pathIndex = 0;
    for (int v = maxNodeIndex; v != -1; v = parent[v]) {
      path[pathIndex++] = v;
    }
    for (int i = pathIndex - 1; i >= 0; --i) {
      fout << (char)('A' + path[i]);
      if (i != 0)
        fout << " ";
    }
    fout << " " << dist[maxNodeIndex] << "\n";
  }

  return "";
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  pair<int, pair<int, int>> edges[NodeMaxCount * NodeMaxCount];
  int edgeCount = 0;
  int parent[NodeMaxCount];
  int rank[NodeMaxCount] = {0};

  for (int i = 0; i < NodeMaxCount; ++i) {
    parent[i] = i;
  }

  for (int i = 0; i < NodeMaxCount - 1; ++i) {
    for (int j = 0; j < NodeMaxCount - 1; ++j) {
      if (edge[i][j] == 1 && exclude[i][j] != 1) {
        edges[edgeCount++] = {weight[i][j], {i, j}};
      }
    }
  }

  sort(edges, edges + edgeCount,
       [](const pair<int, pair<int, int>> &a,
          const pair<int, pair<int, int>> &b) {
         if (a.first == b.first) {
           if (a.second.first == b.second.first) {
             return a.second.second < b.second.second;
           }
           return a.second.first < b.second.first;
         }
         return a.first < b.first;
       });

  int mst_cost = 0;
  int mst_edges = 0;
  string edges_result[100];
  int result_count = 0;

  for (int i = 0; i < NodeMaxCount - 1; ++i) {
    for (int j = 0; j < NodeMaxCount - 1; ++j) {
      if (include[i][j] == 1) {
        if (findSet(parent, i) != findSet(parent, j)) {
          unionSets(parent, rank, i, j);
          char edge_str[100];
          snprintf(edge_str, sizeof(edge_str), "%c %c %d\n", 'A' + i, 'A' + j,
                   weight[i][j]);
          edges_result[result_count++] = edge_str;
          mst_cost += weight[i][j];
          mst_edges++;
        }
      }
    }
  }

  for (int i = 0; i < edgeCount; ++i) {
    int u = edges[i].second.first;
    int v = edges[i].second.second;
    int w = edges[i].first;

    if (findSet(parent, u) != findSet(parent, v)) {
      unionSets(parent, rank, u, v);
      char edge_str[100];
      snprintf(edge_str, sizeof(edge_str), "%c %c %d\n", 'A' + u, 'A' + v, w);
      edges_result[result_count++] = edge_str;
      mst_cost += w;
      mst_edges++;
    }
  }

  sort(edges_result, edges_result + result_count,
       [](const string &a, const string &b) {
         int weight_a = stoi(a.substr(a.find_last_of(' ') + 1));
         int weight_b = stoi(b.substr(b.find_last_of(' ') + 1));
         return weight_a < weight_b;
       });

  for (int i = 0; i < result_count; ++i) {
    fout << edges_result[i];
  }
  return mst_cost;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}