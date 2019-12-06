// Manage flight path with linked list
#include <stdio.h>
#include <stdlib.h>
#include "Path.h"

/* Constructor 
Path::Path(char src, char dst)
{
    this->src = src;
    this->dst = dst;
}*/
void Path::init(char src, char dst)
{
    this->src = src;
    this->dst = dst;
}

/* Add path node to the head of the linked list */
void Path::add(pathnode pnode)
{
    pathnode *new_node = (pathnode *)malloc(sizeof(pathnode));
    new_node->city = pnode.city;
    new_node->departure_time = pnode.departure_time;
    new_node->arrival_time = pnode.arrival_time;
    new_node->date = pnode.date;
    new_node->next = path;
    path = new_node;

    /* calculate flight time */
    if (new_node->arrival_time < new_node->departure_time)
    {
        flight_time += (new_node->arrival_time + 1440 - new_node->departure_time);
    }
    else
    {
        flight_time += (new_node->arrival_time - new_node->departure_time);
    }
    size++;
}

/* Print path */
void Path::print()
{
    pathnode *cur = path;
    
    printf("Path(source: %c / destination: %c)\n", src, dst);
    printf("Flight Time %02d:%02d\n", flight_time / 60, flight_time % 60);
    printf("%c ---(dep %02d:%02d[%02d], arr %02d:%02d[%02d])---> ", cur->city,
        cur->departure_time / 60, cur->departure_time % 60,
        (cur->arrival_time < cur->departure_time) ? (cur->date + 30) % 32 : cur->date,
        cur->arrival_time   / 60, cur->arrival_time   % 60, cur->date);

    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("%c\n%c ---(dep %02d:%02d[%02d], arr %02d:%02d[%02d])---> ",
            cur->city, cur->city,
            cur->departure_time / 60, cur->departure_time % 60,
            (cur->arrival_time < cur->departure_time) ? (cur->date + 30) % 32 : cur->date,
            cur->arrival_time   / 60, cur->arrival_time   % 60, cur->date);
    }
    printf("%c\n", dst);
}