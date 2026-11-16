#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "util.h"

void PrintUsage()
{
    std::fprintf(stderr, "Usage: ./PJ3 <InputFile> <GraphType> <Flag>\n");
}

static bool IsValidGraphType(const char *graphType)
{
    if (graphType == nullptr)
        return false;

    return std::strcmp(graphType, "DirectedGraph") == 0 ||
           std::strcmp(graphType, "UndirectedGraph") == 0;
}

static bool IsValidFlag(const char *flagString)
{
    if (flagString == nullptr)
        return false;

    return std::strcmp(flagString, "0") == 0 ||
           std::strcmp(flagString, "1") == 0;
}

bool CheckCommandLine(int argc, char **argv)
{
    if (argc != 4)
        return false;

    if (!IsValidGraphType(argv[2]))
        return false;

    if (!IsValidFlag(argv[3]))
        return false;

    return true;
}

bool IsDirectedGraph(const char *graphType)
{
    return graphType != nullptr && std::strcmp(graphType, "DirectedGraph") == 0;
}

int GetFlag(const char *flagString)
{
    if (flagString == nullptr)
        return -1;

    return std::atoi(flagString);
}

pGRAPH ReadGraph(const char *inputFile, const char *graphType, int flag)
{
    if (inputFile == nullptr || graphType == nullptr)
        return nullptr;

    FILE *fp = std::fopen(inputFile, "r");
    if (fp == nullptr)
    {
        std::fprintf(stderr, "Error: cannot open file %s.\n", inputFile);
        return nullptr;
    }

    int n = 0;
    int m = 0;

    if (std::fscanf(fp, "%d %d", &n, &m) != 2 || n <= 0 || m < 0)
    {
        std::fprintf(stderr, "Error: invalid graph file format.\n");
        std::fclose(fp);
        return nullptr;
    }

    bool directed = IsDirectedGraph(graphType);
    pGRAPH graph = CreateGraph(n, m, directed);

    for (int i = 0; i < m; i++)
    {
        int edgeIndex = 0;
        int u = 0;
        int v = 0;
        double weight = 0.0;

        if (std::fscanf(fp, "%d %d %d %lf", &edgeIndex, &u, &v, &weight) != 4)
        {
            std::fprintf(stderr, "Error: invalid edge in graph file.\n");
            DestroyGraph(graph);
            std::fclose(fp);
            return nullptr;
        }

        if (flag == 1)
        {
            InsertEdgeRear(graph, edgeIndex, u, v, weight);
            if (!directed)
                InsertEdgeRear(graph, edgeIndex, v, u, weight);
        }
        else
        {
            InsertEdgeFront(graph, edgeIndex, u, v, weight);
            if (!directed)
                InsertEdgeFront(graph, edgeIndex, v, u, weight);
        }
    }

    std::fclose(fp);
    return graph;
}
