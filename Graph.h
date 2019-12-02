// Manage world map with graph
#ifndef GRAPH_H
#define GRAPH_H

#include "Path.h"

typedef struct graphnode
{
    char city;
    int distance;
    struct graphnode *next;
} graphnode;

class Graph
{
private:

    static const int VERTEX_CNT = 26;
    static const int EDGE_CNT = 100;
    static const int RANDOM_SEED = 324798432;

    graphnode **vertices;
    // Maybe need timetable in here or in find_path function's parameter
    // Timetable tt;
    int distance[VERTEX_CNT];
    int visit[VERTEX_CNT];

public:

    // Constructor. Initialize graph setting
    Graph();

    // Make bi-directional edge between node1 and node2 with distance
    void input_node(graphnode *node1, graphnode *node2, int distance);

    // Randomly generate graph edges
    void random_generate();

    // Print graph in linked list format
    void print();

    // Find shortest path using Dijkstra algorithm
    // Maybe need timetable in this function's parameter or member variable of this class
    // What if 31 -> 1?
    Path find_path(char source, char destination, int depature_time);
};

#endif