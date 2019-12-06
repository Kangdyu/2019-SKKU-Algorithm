// Priority Queue (Min Heap) for Dijkstra Algorithm
#include <stdio.h>
#include "PriorityQueue.h"

void PriorityQueue::swap(heapnode *n1, heapnode *n2)
{
    heapnode tmp;
    tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

/* Make this heap min heap (bottom to top) */
void PriorityQueue::heapify_up(int index)
{
    int parent = (index - 1) / 2;

    while (min_heap[parent].weight > min_heap[index].weight)
    {
        swap(&min_heap[parent], &min_heap[index]);
        heapify_up(parent);
    }
}

/* Make this heap min heap (top to bottom) */
void PriorityQueue::heapify_down(int index)
{
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int min = index;

    if (left_child < heap_size)
    {
        if (min_heap[left_child].weight < min_heap[min].weight)
            min = left_child;
    }
    if (right_child < heap_size)
    {
        if (min_heap[right_child].weight < min_heap[min].weight)
            min = right_child;
    }

    if (min != index)
    {
        swap(&min_heap[min], &min_heap[index]);
        heapify_down(min);
    }
}

/* Push new heap node and make min heap */
void PriorityQueue::push(int city, int weight, int distance, int date, int time)
{
    if (heap_size >= HEAP_MAX)
    {
        printf("Queue is full. Failed to push.\n");
        return;
    }
    heapnode new_node;
    new_node.city = city;
    new_node.weight = weight;
    new_node.distance = distance;
    new_node.date = date;
    new_node.time = time;

    min_heap[heap_size] = new_node;
    heapify_up(heap_size);
    heap_size++;
}

/* Return minimum heap node, and then keep this heap min heap */
heapnode PriorityQueue::pop()
{
    heapnode ret;

    if (heap_size == 0)
    {
        ret.city = -1;
        ret.weight = -1;
        printf("Queue is empty. Failed to pop.\n");
        return ret;
    }

    ret = min_heap[0];
    min_heap[0] = min_heap[heap_size - 1];
    heap_size--;

    heapify_down(0);

    return ret;
}

/* Print priority queue */
void PriorityQueue::print()
{
    for (int i = 0; i < heap_size; i++)
        printf("{%d, %d, %d, %d, %d}\n", min_heap[i].city, min_heap[i].weight, min_heap[i].distance, min_heap[i].date, min_heap[i].time);
}

/* Get priority queue's size */
int PriorityQueue::get_size()
{
    return heap_size;
}