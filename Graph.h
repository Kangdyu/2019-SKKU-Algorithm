// Manage world map with graph
#ifndef GRAPH_H
#define GRAPH_H

#include "Path.h"
#include "TimeTable.h"

typedef struct graphnode
{
    char city;
    int x;
    int y;
    int distance;
    struct graphnode *next;
} graphnode;

class Graph
{
private:

    static const int VERTEX_CNT = 26;
    static const int EDGE_CNT = 100;
    static const int RANDOM_SEED = 324798432;
    static const int INF = 2147483647;

    graphnode **vertices;

public:

    /* Constructor. Initialize graph settings */
    Graph();

    /* Make bi-directional edge between node1 and node2 with distance */
    void input_node(graphnode *node1, graphnode *node2, int distance);

    /* Randomly generate city's coordinates and graph edges
     * Also, set time table's city information */
    void random_generate(TimeTable *tt);

    /* Print graph in linked list format */
    void print();

    /* Find shortest path using Dijkstra algorithm
     * Dijkstra algorithm's graph weight: distance between two cities + transfer wait time
     * Return: Path object (has shortest path information) */
    Path find_path(char source, char destination, int departure_date, TimeTable tt);
};

#endif