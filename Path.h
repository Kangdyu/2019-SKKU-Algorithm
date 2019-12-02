// Manage flight path with linked list
#ifndef PATH_H
#define PATH_H

typedef struct pathnode
{
    char city;
    int departure_time;
    int arrival_time;
    struct pathnode *next;
} pathnode;

class Path
{
private:

    char src;
    char dst;
    pathnode *path = NULL;

public:

    // Constructor
    Path(char src, char dst);

    // Add path
    void add(char city, int depature_time, int arrival_time);

    // Print path
    void print();

    /* getter */
    char get_src() { return src; }
    char get_dst() { return dst; }
    /* ====== */
};

#endif