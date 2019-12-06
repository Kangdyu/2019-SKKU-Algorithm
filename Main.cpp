#include <stdio.h>
#include "Graph.h"
#include "Path.h"
#include "PriorityQueue.h"
#include "TimeTable.h"

/*
int main()
{
    TimeTable tt;
    Graph graph;
    Path path;

    tt.random_generate();

    // Make graph object
    graph.random_generate(&tt);
    tt.print();
    graph.print();

    printf("\n");
    // Make path object
    
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (i != j)
            {
                path = graph.find_path(i + 97, j + 97, 31, tt);
                path.print();
                printf("\n");
            }
        }
    }
    
    //Path path = graph.find_path('c', 'w', 31, tt);
    //path.print();

    return 0;
}
*/