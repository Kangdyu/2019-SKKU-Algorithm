// Manage flight path with linked list
#ifndef PATH_H
#define PATH_H

typedef struct pathnode
{
    char city;
    int departure_time;
    int arrival_time;
    int date;
    struct pathnode *next;
} pathnode;

class Path
{
private:

    int size = 0;
    char src;
    char dst;
    int flight_time = 0;
    pathnode *path = NULL;

public:

    /* Constructor */
    //Path(char src, char dst);
    void init(char src, char dst);

    /* Add path node to the head of the linked list */
    void add(pathnode pnode);

    /* Print path */
    void print();

    /* getters */
    char get_src() { return src; }
    char get_dst() { return dst; }
    int get_size() { return size; }
};

#endif