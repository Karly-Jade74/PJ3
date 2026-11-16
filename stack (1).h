#ifndef STACK_H
#define STACK_H

#include "data_structures.h"

// Allocate a new stack
pSTACK InitializeStack(int capacity);

// Free memory used by the stack
void DestroyStack(pSTACK stack);

// Returns true if stack is empty
bool StackIsEmpty(pSTACK stack);

// Returns true if stack is full
bool StackIsFull(pSTACK stack);

// Push a vertex pointer onto the stack
void Push(pSTACK stack, pVERTEX vertex);

// Remove and return the top vertex
pVERTEX Pop(pSTACK stack);

// Return top vertex without removing it
pVERTEX Peek(pSTACK stack);

#endif