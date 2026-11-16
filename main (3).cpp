#include <cstdio>
#include <cstring>

#include "main.h"

int main(int argc, char **argv)
{
    if (!CheckCommandLine(argc, argv))
    {
        PrintUsage();
        return 1;
    }

    int flag = GetFlag(argv[3]);
    pGRAPH graph = ReadGraph(argv[1], argv[2], flag);

    if (graph == nullptr)
    {
        return 1;
    }

    pHEAP heap = InitializeHeap(graph->n);
    pSTACK stack = InitializeStack(graph->n);

    int lastSource = -1;
    int lastDestination = -1;
    bool hasComputation = false;
    bool lastWasSinglePair = false;

    char instruction[128];

    while (std::scanf("%127s", instruction) == 1)
    {
        if (std::strcmp(instruction, "Stop") == 0)
        {
            break;
        }
        else if (std::strcmp(instruction, "PrintADJ") == 0)
        {
            PrintAdjacencyList(graph);
        }
        else if (std::strcmp(instruction, "SinglePair") == 0)
        {
            int source = 0;
            int destination = 0;

            if (std::scanf("%d %d", &source, &destination) != 2)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                break;
            }

            if (source < 1 || source > graph->n || destination < 1 || destination > graph->n)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                continue;
            }

            Dijkstra(graph, source, destination, heap);
            lastSource = source;
            lastDestination = destination;
            hasComputation = true;
            lastWasSinglePair = true;
        }
        else if (std::strcmp(instruction, "SingleSource") == 0)
        {
            int source = 0;

            if (std::scanf("%d", &source) != 1)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                break;
            }

            if (source < 1 || source > graph->n)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                continue;
            }

            Dijkstra(graph, source, -1, heap);
            lastSource = source;
            lastDestination = -1;
            hasComputation = true;
            lastWasSinglePair = false;
        }
        else if (std::strcmp(instruction, "PrintLength") == 0)
        {
            int source = 0;
            int destination = 0;

            if (std::scanf("%d %d", &source, &destination) != 2)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                break;
            }

            bool valid = hasComputation &&
                         source == lastSource &&
                         source >= 1 && source <= graph->n &&
                         destination >= 1 && destination <= graph->n;

            if (lastWasSinglePair && destination != lastDestination)
                valid = false;

            if (!valid)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                continue;
            }

            PrintLength(graph, source, destination);
        }
        else if (std::strcmp(instruction, "PrintPath") == 0)
        {
            int source = 0;
            int destination = 0;

            if (std::scanf("%d %d", &source, &destination) != 2)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                break;
            }

            bool valid = hasComputation &&
                         source == lastSource &&
                         source >= 1 && source <= graph->n &&
                         destination >= 1 && destination <= graph->n;

            if (lastWasSinglePair && destination != lastDestination)
                valid = false;

            if (!valid)
            {
                std::fprintf(stderr, "Error: Invalid instruction.\n");
                continue;
            }

            PrintPath(graph, source, destination, stack);
        }
        else
        {
            std::fprintf(stderr, "Error: Invalid instruction.\n");
        }
    }

    DestroyStack(stack);
    DestroyHeap(heap);
    DestroyGraph(graph);

    return 0;
}
