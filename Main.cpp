#include <stdio.h>
#include "Graph.h"
#include "Path.h"
#include "PriorityQueue.h"

int main()
{
    // Make graph object
    Graph graph;

    graph.random_generate();
    graph.print();

    printf("\n");
    // Make path object
    Path path = graph.find_path('y', 'j', 1);
    path.print();

    return 0;
}