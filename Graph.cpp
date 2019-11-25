// Manage world map with graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Graph.h"

// Constructor. Initialize graph setting
Graph::Graph()
{
    //srand(RANDOM_SEED);
    srand(time(NULL));
    vertices = (gnode **)malloc(sizeof(gnode *) * VERTEX_CNT);
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        vertices[i] = (gnode *)malloc(sizeof(gnode));
        vertices[i]->city = 97 + i;
        vertices[i]->distance = 0;
        vertices[i]->next = NULL;
    }
}

// Make bi-directional edge between node1 and node2 with distance
void Graph::input_node(gnode *node1, gnode *node2, int distance)
{
    gnode *new_node1 = (gnode *)malloc(sizeof(gnode));
    new_node1->city = node2->city;
    new_node1->next = NULL;
    new_node1->distance = distance;

    gnode *target = NULL;
    gnode *cur = node1;
    while (cur != NULL)
    {
        target = cur;
        cur = cur->next;
    }
    target->next = new_node1;
    
    gnode *new_node2 = (gnode *)malloc(sizeof(gnode));
    new_node2->city = node1->city;
    new_node2->next = NULL;
    new_node2->distance = distance;

    target = NULL;
    cur = node2;
    while (cur != NULL)
    {
        target = cur;
        cur = cur->next;
    }
    target->next = new_node2;
}

// Randomly generate graph edges
void Graph::random_generate()
{
    int remained_edges = 100;
    int vertices_in_2d[VERTEX_CNT][VERTEX_CNT] = { 0, };

    for (int i = 0; i < VERTEX_CNT && remained_edges > 0; i++)
    {
        for (int j = 0; j < VERTEX_CNT && remained_edges > 0; j++)
        {
            int decision = rand() % 2;
            if (i != j && decision == 1 && vertices_in_2d[i][j] == 0)
            {
                // can be 0?
                int dist = rand() % 3000 + 1;
                input_node(vertices[i], vertices[j], dist);
                vertices_in_2d[i][j] = vertices_in_2d[j][i] = 1;
                remained_edges--;
            }
        }
    }
}

// Print graph in linked list format
void Graph::print()
{
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        gnode *cur = vertices[i];
        printf("city: %c\n", cur->city);
        while (cur != NULL)
        {
            printf("%c(%d), ", cur->city, cur->distance);
            cur = cur->next;
        }
        printf("\n");
    }
}

// Find shortest path using Dijkstra algorithm
Path Graph::find_path(char src, char dst, int depature_time)
{
    Path path = Path(src, dst);

    return path;
}