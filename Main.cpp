#include <stdio.h>
#include "Graph.h"
#include "Path.h"
#include "PriorityQueue.h"

int main()
{
    // Make graph object
    Graph graph = Graph();
    
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

    printf("\n\n");
    PriorityQueue pq;
    pq.push(0, 10);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");
    pq.push(0, 20);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");
    pq.push(1, 5);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");
    pq.push(1, 3);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");
    pq.push(2, 4);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");
    heapnode hn;
    hn = pq.pop();
    pq.print();
    printf("popped:: city: %d, weight: %d\n", hn.city, hn.weight);
    printf("size: %d\n", pq.size());
    printf("--------\n");
    hn = pq.pop();
    pq.print();
    printf("popped:: city: %d, weight: %d\n", hn.city, hn.weight);
    printf("size: %d\n", pq.size());
    printf("--------\n");
    hn = pq.pop();
    pq.print();
    printf("popped:: city: %d, weight: %d\n", hn.city, hn.weight);
    printf("size: %d\n", pq.size());
    printf("--------\n");
    pq.push(5, 0);
    pq.print();
    printf("size: %d\n", pq.size());
    printf("--------\n");

    return 0;
}