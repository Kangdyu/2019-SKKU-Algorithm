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

void PriorityQueue::heapify_up(int index)
{
    int parent = (index - 1) / 2;

    while (min_heap[parent].weight > min_heap[index].weight)
    {
        swap(&min_heap[parent], &min_heap[index]);
        heapify_up(parent);
    }
}

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

void PriorityQueue::push(int city, int weight)
{
    if (heap_size >= HEAP_MAX)
    {
        printf("Queue is full. Failed to push.\n");
        return;
    }
    heapnode new_node;
    new_node.city = city;
    new_node.weight = weight;

    min_heap[heap_size] = new_node;
    heapify_up(heap_size);
    heap_size++;
}

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

void PriorityQueue::print()
{
    for (int i = 0; i < heap_size; i++)
        printf("{%d, %d}\n", min_heap[i].city, min_heap[i].weight);
}

int PriorityQueue::size()
{
    return heap_size;
}