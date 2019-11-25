#include <stdio.h>
#include "Graph.h"
#include "Path.h"

int main()
{
    // Make graph object
    Graph graph = Graph();

    graph.random_generate();
    graph.print();

    // Make path object
    Path path = Path('a', 'd');
    //Path path = graph.find_path('a', 'd', 1000);
    /* Will be used like this in Graph::find_path() */
    path.add('a', 0, 1);
    path.add('b', 2, 3);
    path.add('c', 4, 5);
    path.add('d', 6, 7);
    path.print();
    /**/

    return 0;
}