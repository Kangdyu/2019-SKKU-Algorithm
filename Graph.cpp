// Manage world map with graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Graph.h"
#include "PriorityQueue.h"

/* Constructor. Initialize graph settings */
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

/* Make bi-directional edge between node1 and node2 with distance */
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

/* Randomly generate city's coordinates and graph edges
 * Also, set time table's city information */
void Graph::random_generate(TimeTable *tt)
{
    int xs[VERTEX_CNT];
    int ys[VERTEX_CNT];
    int reroll = 0;
    int remained_edges = 100;
    int vertices_in_2d[VERTEX_CNT][VERTEX_CNT] = { 0, };

    /* 1. Initialize settings */
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        xs[i] = -1;
        ys[i] = -1;
    }

    /* 2. Generate city's coordinates */
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
    /* debugging
    for (int i = 0; i < VERTEX_CNT; i++)
        printf("city %c: (%d, %d)\n", vertices[i]->city, vertices[i]->x, vertices[i]->y);
    */
    /* 3. Generate edges */
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

/* Print graph in linked list format */
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

/* Find shortest path using Dijkstra algorithm
 * Dijkstra algorithm's graph weight: distance between two cities + transfer wait time
 * Return: Path object (has shortest path information) */
Path Graph::find_path(char source, char destination, int departure_date, TimeTable tt)
{
    // will be returned
    Path path;
    path.init(source, destination);

    // priority queue for dijkstra
    PriorityQueue pq;
    // store shortest distance from source to any cities
    int distance[VERTEX_CNT];
    // pathnode array for back-tracking. will be added to return variable 'path'
    pathnode prev[VERTEX_CNT];
    /* convert char to int (for array index) */
    int src = source - 97;
    int dst = destination - 97;
    // to use array(start from 0), subtract 1
    int date = departure_date - 1;

    /* 1. Initialize Dijkstra settings */
    for (int i = 0; i < VERTEX_CNT; i++)
    {
        distance[i] = INF;
        prev[i].city = -1;
    }
    distance[src] = 0;
    pq.push(src, 0, 0, date, 0);

    /* 2. Dijkstra algorithm (until queue is empty) */
    while (pq.get_size() != 0)
    {
        /* 2-1. Get current city's information */
        heapnode cur = pq.pop();
        int cur_city = cur.city;
        int cur_weight = cur.weight;
        int cur_date = cur.date;
        // current time after arriving in this city from previous city
        int cur_time = cur.time + ceil(cur.distance/500.0 * 60);
        if (cur_time >= 1440)
        {
            cur_time %= 1440;
            cur_date = (cur_date + 1) % 31;
        }
        /* 2-2. Check all adjacent cities */
        graphnode *adj = vertices[cur_city]->next;
        while (adj != NULL)
        {
            if (prev[cur_city].city == adj->city - 97)
            {
                adj = adj->next;
                continue;
            }
            // arrival date (current city -> adjacent city)
            int arrival_date = cur_date;
            // convert char to int (for array index)
            int adj_city = adj->city - 97;
            // seek departure time from time table (current city -> adjacent city)
            int dep_time = tt.seek(cur_city, adj_city, arrival_date);
            // additional weight value for considering transfer wait time
            int wait_weight = dep_time - cur_time;
            // if departure time passed
            if (dep_time < cur_time)
            {
                wait_weight += (1440 - dep_time);
                arrival_date = (arrival_date + 1) % 31;
                // seek next day's departure time
                dep_time = tt.seek(cur_city, adj_city, arrival_date);
                wait_weight += dep_time;
            }
            
            // convert time to distance
            wait_weight = ceil(wait_weight/60.0) * 500;

            // if this path is shorter than previous path, update information
            if (distance[adj_city] > adj->distance + distance[cur_city] + wait_weight)
            {
                distance[adj_city] = adj->distance + distance[cur_city] + wait_weight;
                pq.push(adj_city, distance[adj_city], adj->distance, arrival_date, dep_time);
                /* store informations for back-tracking */
                prev[adj_city].city = cur_city + 97;
                prev[adj_city].departure_time = dep_time;
                prev[adj_city].arrival_time = dep_time + ceil(adj->distance/500.0 * 60);
                if (prev[adj_city].arrival_time >= 1440)
                {
                    prev[adj_city].arrival_time %= 1440;
                    prev[adj_city].date = (arrival_date + 1) % 31 + 1;
                }
                else
                {
                    prev[adj_city].date = (arrival_date) % 31 + 1;
                }
            }
            // check next adjacent city
            adj = adj->next;
        }
    }

    /* 3. Add path using the result of Dijkstra's algorithm (back-tracking) */
    while (prev[dst].city != -1)
    {
        path.add(prev[dst]);
        dst = prev[dst].city - 97;
    }

    return path;
}