
#include <cstdio>
#include <cfloat>
#include "graph.h"

pGRAPH CreateGraph(int vertices, int edges, bool directed)
{
    pGRAPH graph = new GRAPH;

    graph->n = vertices;
    graph->m = edges;
    graph->directed = directed;

    graph->V = new pVERTEX[vertices + 1];
    graph->ADJ = new pNODE[vertices + 1];

    for (int i = 0; i <= vertices; i++)
    {
        graph->ADJ[i] = nullptr;
        graph->V[i] = nullptr;
    }

    for (int i = 1; i <= vertices; i++)
    {
        graph->V[i] = new VERTEX;
        graph->V[i]->index = i;
        graph->V[i]->color = WHITE;
        graph->V[i]->key = DBL_MAX;
        graph->V[i]->pi = 0;
        graph->V[i]->position = 0;
    }

    return graph;
}

void DestroyGraph(pGRAPH graph)
{
    if (graph == nullptr)
        return;

    if (graph->ADJ != nullptr)
    {
        for (int i = 1; i <= graph->n; i++)
        {
            pNODE current = graph->ADJ[i];
            while (current != nullptr)
            {
                pNODE next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] graph->ADJ;
    }

    if (graph->V != nullptr)
    {
        for (int i = 1; i <= graph->n; i++)
        {
            delete graph->V[i];
        }
        delete[] graph->V;
    }

    delete graph;
}

static pNODE CreateNode(int edgeIndex, int u, int v, double weight)
{
    pNODE node = new NODE;

    node->index = edgeIndex;
    node->u = u;
    node->v = v;
    node->w = weight;
    node->next = nullptr;

    return node;
}

void InsertEdgeFront(pGRAPH graph, int edgeIndex, int u, int v, double weight)
{
    if (graph == nullptr || u < 1 || u > graph->n)
        return;

    pNODE node = CreateNode(edgeIndex, u, v, weight);
    node->next = graph->ADJ[u];
    graph->ADJ[u] = node;
}

void InsertEdgeRear(pGRAPH graph, int edgeIndex, int u, int v, double weight)
{
    if (graph == nullptr || u < 1 || u > graph->n)
        return;

    pNODE node = CreateNode(edgeIndex, u, v, weight);

    if (graph->ADJ[u] == nullptr)
    {
        graph->ADJ[u] = node;
        return;
    }

    pNODE current = graph->ADJ[u];
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = node;
}

void PrintAdjacencyList(pGRAPH graph)
{
    if (graph == nullptr)
        return;

    for (int i = 1; i <= graph->n; i++)
    {
        std::printf("ADJ[%d]:", i);

        pNODE current = graph->ADJ[i];
        while (current != nullptr)
        {
            std::printf("-->[%d %d: %4.2lf]", current->u, current->v, current->w);
            current = current->next;
        }

        std::printf("\n");
    }
}

void InitializeSingleSource(pGRAPH graph, int source)
{
    if (graph == nullptr)
        return;

    for (int i = 1; i <= graph->n; i++)
    {
        graph->V[i]->index = i;
        graph->V[i]->color = WHITE;
        graph->V[i]->key = DBL_MAX;
        graph->V[i]->pi = 0;
        graph->V[i]->position = 0;
    }

    if (source >= 1 && source <= graph->n)
    {
        graph->V[source]->key = 0.0;
        graph->V[source]->color = GRAY;
    }
}

void Relax(pGRAPH graph, int u, pNODE edge, pHEAP heap)
{
    if (graph == nullptr || edge == nullptr || heap == nullptr)
        return;

    int v = edge->v;

    if (u < 1 || u > graph->n || v < 1 || v > graph->n)
        return;

    if (graph->V[u]->key == DBL_MAX)
        return;

    double newKey = graph->V[u]->key + edge->w;

    if (newKey < graph->V[v]->key)
    {
        graph->V[v]->key = newKey;
        graph->V[v]->pi = u;

        if (graph->V[v]->color == GRAY && graph->V[v]->position > 0)
        {
            DecreaseKey(heap, graph->V[v]->position, newKey);
        }
    }
}

void Dijkstra(pGRAPH graph, int source, int destination, pHEAP heap)
{
    if (graph == nullptr || heap == nullptr)
        return;

    heap->size = 0;

    InitializeSingleSource(graph, source);

    if (source < 1 || source > graph->n)
        return;

    Insert(heap, graph->V[source]);

    while (!HeapIsEmpty(heap))
    {
        pVERTEX minVertex = ExtractMin(heap);
        if (minVertex == nullptr)
            break;

        int u = minVertex->index;

        if (u == destination)
        {
            minVertex->color = BLACK;
            break;
        }

        pNODE edge = graph->ADJ[u];
        while (edge != nullptr)
        {
            int v = edge->v;

            if (v >= 1 && v <= graph->n)
            {
                if (graph->V[v]->color == WHITE)
                {
                    graph->V[v]->color = GRAY;
                    Relax(graph, u, edge, heap);
                    Insert(heap, graph->V[v]);
                }
                else if (graph->V[v]->color == GRAY)
                {
                    Relax(graph, u, edge, heap);
                }
            }

            edge = edge->next;
        }

        minVertex->color = BLACK;
    }
}

void PrintLength(pGRAPH graph, int source, int destination)
{
    if (graph == nullptr || source < 1 || source > graph->n ||
        destination < 1 || destination > graph->n ||
        graph->V[destination]->key == DBL_MAX)
    {
        std::printf("There is no path from %d to %d.\n", source, destination);
        return;
    }

    std::printf("The length of the shortest path from %d to %d is:%9.2lf\n",
                source, destination, graph->V[destination]->key);
}

void PrintPath(pGRAPH graph, int source, int destination, pSTACK stack)
{
    if (graph == nullptr || stack == nullptr || source < 1 || source > graph->n ||
        destination < 1 || destination > graph->n ||
        graph->V[destination]->key == DBL_MAX)
    {
        std::printf("There is no path from %d to %d.\n", source, destination);
        return;
    }

    stack->top = -1;

    int current = destination;
    while (current != 0)
    {
        Push(stack, graph->V[current]);

        if (current == source)
            break;

        current = graph->V[current]->pi;
    }

    if (StackIsEmpty(stack) || Peek(stack)->index != source)
    {
        stack->top = -1;
        std::printf("There is no path from %d to %d.\n", source, destination);
        return;
    }

    std::printf("The shortest path from %d to %d is:\n", source, destination);

    while (!StackIsEmpty(stack))
    {
        pVERTEX vertex = Pop(stack);
        std::printf("[%d:%8.2lf]", vertex->index, vertex->key);

        if (!StackIsEmpty(stack))
            std::printf("-->");
        else
            std::printf(".\n");
    }
}
