// Manage flight path with linked list
#ifndef PATH_H
#define PATH_H

typedef struct pathnode
{
    char city;
    int departure_time;
    struct pathnode *next;
} pnode;

class Path
{
private:

    pnode *path = NULL;

public:

    // Add path
    void add(char city, int depature_time);

    // Print path
    void print();
};

#endif