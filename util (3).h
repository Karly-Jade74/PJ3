#ifndef UTIL_H
#define UTIL_H

#include "data_structures.h"
#include "graph.h"

// Prints the required usage message to stderr.
void PrintUsage();

// Returns true only when argc, graph type, and flag are valid.
bool CheckCommandLine(int argc, char **argv);

// Returns true for DirectedGraph and false for UndirectedGraph.
bool IsDirectedGraph(const char *graphType);

// Converts the command-line flag string to an int.
int GetFlag(const char *flagString);

pGRAPH ReadGraph(const char *inputFile, const char *graphType, int flag);

#endif
