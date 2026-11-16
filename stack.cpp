#include <iostream>

#include "stack.h"

using namespace std;

pSTACK InitializeStack(int capacity)
{
    pSTACK stack = new STACK;

    stack->capacity = capacity;
    stack->top = -1;

    stack->S = new pVERTEX[capacity];

    return stack;
}

void DestroyStack(pSTACK stack)
{
    delete[] stack->S;
    delete stack;
}

bool StackIsEmpty(pSTACK stack)
{
    return stack->top == -1;
}

bool StackIsFull(pSTACK stack)
{
    return stack->top == stack->capacity - 1;
}

void Push(pSTACK stack, pVERTEX vertex)
{
    if (StackIsFull(stack))
        return;

    stack->top++;

    stack->S[stack->top] = vertex;
}

pVERTEX Pop(pSTACK stack)
{
    if (StackIsEmpty(stack))
        return nullptr;

    pVERTEX vertex = stack->S[stack->top];

    stack->top--;

    return vertex;
}

pVERTEX Peek(pSTACK stack)
{
    if (StackIsEmpty(stack))
        return nullptr;

    return stack->S[stack->top];
}