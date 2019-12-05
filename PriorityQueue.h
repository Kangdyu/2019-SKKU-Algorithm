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

    void heapify_up(int index);

    void heapify_down(int index);

    // push into queue
    void push(int city, int weight, int destination, int date, int time);

    // pop queue and get min heap node
    heapnode pop();

    // print prioirty queue
    void print();

    // get queue size
    int get_size();

};


#endif