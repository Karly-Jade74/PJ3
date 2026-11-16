// Your Name: Karly O'Brien
// ASU ID: 11232791029

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

enum COLOR
{
    WHITE,
    GRAY,
    BLACK
};
typedef struct TAG_VERTEX
{
    int index;// Vertex number
    COLOR color;// WHITE, GRAY, BLACK
    double key;// Current shortest distance
    int pi;// Predecessor vertex
    int position;// Position inside heap

} VERTEX;

typedef VERTEX *pVERTEX;
typedef struct TAG_NODE
{
    int index;// Edge index
    int u;// Source vertex
    int v;// Destination vertex
    double w;// Edge weight

    struct TAG_NODE *next;

} NODE;

typedef NODE *pNODE;
typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;
typedef struct TAG_HEAP
{
    int capacity;
    int size;

    // Heap array of vertex pointers
    pELEMENT *H;

} HEAP;

typedef HEAP *pHEAP;
typedef struct TAG_STACK
{
    int capacity;
    int top;

    pVERTEX *S;

} STACK;

typedef STACK *pSTACK;

#endif