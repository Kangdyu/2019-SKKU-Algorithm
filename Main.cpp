#include <stdio.h>
#include "Graph.h"
#include "Path.h"

int main()
{
    // Make graph object
    Graph graph = Graph();
    // Make path object
    Path path;

    graph.random_generate();
    graph.print();

    //path = graph.find_path('a', 'd', 1000);
    /* Will be used like this in Graph::find_path() */
    path.add('a', 0);
    path.add('b', 0);
    path.add('c', 0);
    path.add('d', 0);
    path.print();
    /**/

    return 0;
}