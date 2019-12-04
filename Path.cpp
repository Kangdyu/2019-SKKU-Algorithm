// Manage flight path with linked list
#include <stdio.h>
#include <stdlib.h>
#include "Path.h"

// Constructor
Path::Path(char src, char dst)
{
    this->src = src;
    this->dst = dst;
}

// Add path node to the head of the linked list
void Path::add(char city, int departure_time, int arrival_time)
{
    pathnode *new_node = (pathnode *)malloc(sizeof(pathnode));
    new_node->city = city;
    new_node->departure_time = departure_time;
    new_node->arrival_time = arrival_time;
    new_node->next = path;
    path = new_node;

    this->flight_time += (arrival_time - departure_time);
    size++;
}

// Print path
void Path::print()
{
    pathnode *cur = path;
    
    printf("Path(source: %c / destination: %c)\n", src, dst);
    printf("%c(dep: %d, arr: %d) ", cur->city, cur->departure_time, cur->arrival_time);

    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("-> %c(dep: %d, arr: %d) ", cur->city, cur->departure_time, cur->arrival_time);
    }
}