#include <iostream>
#include <cfloat>

#include "heap.h"

using namespace std;


static void BubbleUp(pHEAP heap, int i)
{
    while (i > 1)
    {
        int parent = i / 2;

        if (heap->H[parent]->key <= heap->H[i]->key)
            break;

        pELEMENT temp = heap->H[parent];

        heap->H[parent] = heap->H[i];
        heap->H[i] = temp;

        heap->H[parent]->position = parent;
        heap->H[i]->position = i;

        i = parent;
    }
}

static void Heapify(pHEAP heap, int i)
{
    while (true)
    {
        int left = 2 * i;
        int right = left + 1;

        int smallest = i;

        if (left <= heap->size &&
            heap->H[left]->key < heap->H[smallest]->key)
            smallest = left;

        if (right <= heap->size &&
            heap->H[right]->key < heap->H[smallest]->key)
            smallest = right;

        if (smallest == i)
            break;

        pELEMENT temp = heap->H[i];

        heap->H[i] = heap->H[smallest];
        heap->H[smallest] = temp;

        heap->H[i]->position = i;
        heap->H[smallest]->position = smallest;

        i = smallest;
    }
}

pHEAP InitializeHeap(int capacity)
{
    pHEAP heap = new HEAP;

    heap->capacity = capacity;
    heap->size = 0;

    heap->H = new pELEMENT[capacity + 1];

    return heap;
}

void DestroyHeap(pHEAP heap)
{
    delete[] heap->H;
    delete heap;
}

bool HeapIsEmpty(pHEAP heap)
{
    return heap->size == 0;
}

void Insert(pHEAP heap, pELEMENT element)
{
    if (heap->size == heap->capacity)
        return;

    heap->size++;

    heap->H[heap->size] = element;
    element->position = heap->size;

    BubbleUp(heap, heap->size);
}

pELEMENT ExtractMin(pHEAP heap)
{
    if (HeapIsEmpty(heap))
        return nullptr;

    pELEMENT minimum = heap->H[1];

    heap->H[1] = heap->H[heap->size];
    heap->size--;

    if (heap->size > 0)
    {
        heap->H[1]->position = 1;
        Heapify(heap, 1);
    }

    minimum->position = 0;

    return minimum;
}

void DecreaseKey(pHEAP heap, int position, double newKey)
{
    if (position <= 0 || position > heap->size)
        return;

    if (newKey > heap->H[position]->key)
        return;

    heap->H[position]->key = newKey;

    BubbleUp(heap, position);
}