// Manage world map with graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Graph.h"
#include "PriorityQueue.h"

// Constructor. Initialize graph setting
Graph::Graph()
{
    srand(RANDOM_SEED);
    //srand(time(NULL));
    vertices = (graphnode **)malloc(sizeof(graphnode *) * VERTEX_CNT);
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        vertices[i] = (graphnode *)malloc(sizeof(graphnode));
        vertices[i]->city = 97 + i;
        vertices[i]->distance = 0;
        vertices[i]->next = NULL;
    }
}

// Make bi-directional edge between node1 and node2 with distance
void Graph::input_node(graphnode *node1, graphnode *node2, int distance)
{
    graphnode *new_node1 = (graphnode *)malloc(sizeof(graphnode));
    new_node1->city = node2->city;
    new_node1->distance = distance;
    new_node1->next = node1->next;
    node1->next = new_node1;
    
    graphnode *new_node2 = (graphnode *)malloc(sizeof(graphnode));
    new_node2->city = node1->city;
    new_node2->distance = distance;
    new_node2->next = node2->next;
    node2->next = new_node2;
}

// Randomly generate city's coordinates and graph edges
void Graph::random_generate(TimeTable *tt)
{
    int xs[VERTEX_CNT];
    int ys[VERTEX_CNT];
    int reroll = 0;
    int remained_edges = 100;
    int vertices_in_2d[VERTEX_CNT][VERTEX_CNT] = { 0, };

    for (int i = 0; i < VERTEX_CNT; i++)
    {
        xs[i] = -1;
        ys[i] = -1;
    }

    // generate city's coordinates
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        int x = rand() % 6001;
        int y = rand() % 6001;
        for (int j = 0; j < i; j++)
        {
            if (xs[j] == x && ys[j] == y)
            {
                reroll = 1;
                break;
            }
        }
        if (reroll == 1)
        {
            reroll = 0;
            i--;
            break;
        }
        xs[i] = x;
        ys[i] = y;
        vertices[i]->x = x;
        vertices[i]->y = y;
    }
    // debugging
    for (int i = 0; i < VERTEX_CNT; i++)
        printf("city %c: (%d, %d)\n", vertices[i]->city, vertices[i]->x, vertices[i]->y);

    // generate edges
    for (int i = 0; i < VERTEX_CNT && remained_edges > 0; i++)
    {
        for (int j = 0; j < VERTEX_CNT && remained_edges > 0; j++)
        {
            int decision = rand() % 2;
            if (i != j && decision == 1 && vertices_in_2d[i][j] == 0)
            {
                int dist = sqrt(pow(abs(vertices[i]->x - vertices[j]->x), 2) +
                                pow(abs(vertices[i]->y - vertices[j]->y), 2));
                
                input_node(vertices[i], vertices[j], dist);
                tt->insert_city_info(i, j);
                tt->insert_city_info(j, i);
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
        graphnode *cur = vertices[i];
        printf("city: %c\n", cur->city);
        while (cur != NULL)
        {
            printf("%c(%d), ", cur->city, cur->distance);
            cur = cur->next;
        }
        printf("end\n");
    }
}

// Find shortest path using Dijkstra algorithm
// weight: pathnode's distance
// transfer wait time will be converted to distance at each node (calculate with 500km/h)
Path Graph::find_path(char source, char destination, int departure_date, TimeTable tt)
{
    Path path = Path(source, destination);
    PriorityQueue pq;
    int distance[VERTEX_CNT];
    int prev[VERTEX_CNT];
    int src = source - 97;
    int dst = destination - 97;
    int date = departure_date;

    for (int i = 0; i < VERTEX_CNT; i++)
    {
        distance[i] = INF;
        prev[i] = -1;
    }
    distance[src] = 0;
    pq.push(src, 0, date, 0, 0);

    while (pq.get_size() != 0)
    {
        //pq.print();
        heapnode cur = pq.pop();
        int cur_city = cur.city;
        int cur_weight = cur.weight;
        int cur_date = cur.date;
        // convert distance to time (500km/h)
        int cur_time = cur.time + ceil(cur.distance/500.0 * 6);

        graphnode *adj = vertices[cur_city]->next;
        while (adj != NULL)
        {
            if (prev[cur_city] == adj->city - 97)
            {
                adj = adj->next;
                break;
            }
            int adj_city = adj->city - 97;
            int dep_time = tt.seek(cur_city, adj_city, cur_date);
            int wait_weight = dep_time - cur_time;
            if (dep_time < cur_time)
            {
                wait_weight += (1440 - dep_time);
                dep_time = tt.seek(cur_city, adj_city, ++cur_date);
                wait_weight += dep_time;
            }
            // convert time to distance
            wait_weight = ceil(wait_weight/60.0) * 500;

            if (distance[adj_city] > adj->distance + distance[cur_city] + wait_weight)
            {
                distance[adj_city] = adj->distance + distance[cur_city] + wait_weight;
                pq.push(adj_city, distance[adj_city], adj->distance, cur_date, dep_time);
                prev[adj_city] = cur_city;
            }
            adj = adj->next;
        }
    }

    path.add(dst + 97, 0, 0);
    while (prev[dst] != -1)
    {
        path.add(prev[dst] + 97, 0, 0);
        dst = prev[dst];
    }
    return path;
}