#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

pHEAP InitializeHeap(int capacity);
void DestroyHeap(pHEAP heap);

bool HeapIsEmpty(pHEAP heap);

void Insert(pHEAP heap, pELEMENT element);

pELEMENT ExtractMin(pHEAP heap);

void DecreaseKey(pHEAP heap, int position, double newKey);

#endif