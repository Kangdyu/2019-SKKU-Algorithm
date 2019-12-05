#include <stdio.h>
#include "Graph.h"
#include "Path.h"
#include "PriorityQueue.h"
#include "TimeTable.h"

int main()
{
    TimeTable tt;
    Graph graph;

    tt.random_generate();

    // Make graph object
    graph.random_generate(&tt);
    tt.print();
    graph.print();

    printf("\n");
    // Make path object
    Path path = graph.find_path('a', 'y', 31, tt);
    path.print();

    return 0;
}