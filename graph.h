#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"
#include "heap.h"
#include "stack.h"

typedef struct TAG_GRAPH
{
    int n;// Number of vertices
    int m;// Number of edges

    bool directed;// true = directed graph

    pVERTEX *V;// Array of vertex pointers
    pNODE *ADJ;// Array of adjacency lists

} GRAPH;

typedef GRAPH *pGRAPH;


pGRAPH CreateGraph(int vertices, int edges, bool directed);

void DestroyGraph(pGRAPH graph);


void InsertEdgeFront(
    pGRAPH graph,
    int edgeIndex,
    int u,
    int v,
    double weight);

void InsertEdgeRear(
    pGRAPH graph,
    int edgeIndex,
    int u,
    int v,
    double weight);

void PrintAdjacencyList(pGRAPH graph);

void InitializeSingleSource(
    pGRAPH graph,
    int source);

void Relax(
    pGRAPH graph,
    int u,
    pNODE edge,
    pHEAP heap);

void Dijkstra(
    pGRAPH graph,
    int source,
    int destination,
    pHEAP heap);

void PrintLength(
    pGRAPH graph,
    int source,
    int destination);

void PrintPath(
    pGRAPH graph,
    int source,
    int destination,
    pSTACK stack);

#endif