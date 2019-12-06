// Priority Queue (Min Heap) for Dijkstra Algorithm
#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

typedef struct heapnode
{
    int city;
    int weight;
    int distance;
    int date;
    int time;
} heapnode;

class PriorityQueue
{
private:

    static const int HEAP_MAX = 10000;
    heapnode min_heap[HEAP_MAX];
    int heap_size = 0;

public:
    
    void swap(heapnode *n1, heapnode *n2);

    /* Make this heap min heap (bottom to top) */
    void heapify_up(int index);

    /* Make this heap min heap (top to bottom) */
    void heapify_down(int index);

    /* Push new heap node and make min heap */
    void push(int city, int weight, int distance, int date, int time);

    /* Return minimum heap node, and then keep this heap min heap */
    heapnode pop();

    /* Print priority queue */
    void print();

    /* Get priority queue's size */
    int get_size();

};


#endif