#include <iostream>
#include "graph.h"

int main() {
    Graph g;
    g.addUndirectedEdge("A", "B");
    g.addUndirectedEdge("B", "C");
    g.addUndirectedEdge("A", "C");

    std::cout << g.checkCycle() << std::endl;  // "TRUE" 출력

    Graph g2;
    g2.addUndirectedEdge("A", "B");
    g2.addUndirectedEdge("A", "C");
    g2.addUndirectedEdge("C", "D");

    std::cout << g2.checkCycle() << std::endl;  // "FALSE" 출력

    return 0;
}
