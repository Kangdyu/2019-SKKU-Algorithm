// Manage flight path with linked list
#include <stdio.h>
#include <stdlib.h>
#include "Path.h"

// Add path node to the end of the linked list
void Path::add(char city, int depature_time)
{
    pnode *new_node = (pnode *)malloc(sizeof(pnode));
    new_node->city = city;
    new_node->departure_time = depature_time;
    new_node->next = NULL;

    if (path == NULL)
    {
        path = new_node;
        return;
    }

    pnode *target = NULL;
    pnode *cur = path;

    while (cur != NULL)
    {
        target = cur;
        cur = cur->next;
    }

    target->next = new_node;
}

// Print path
void Path::print()
{
    pnode *cur = path;
    printf("Path\n");
    printf("%c ", cur->city);

    while (cur->next != NULL)
    {
        cur = cur->next;
        printf("-> %c ", cur->city);
    }
}