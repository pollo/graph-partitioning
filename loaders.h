#ifndef LOADERS_H
#define LOADERS_H

#include "graph.h"

#define SLASHDOT_DIRECTED true
#define SLASHDOT_FILE "dataset/soc-Slashdot0811.txt"

#define AMAZON_DIRECTED true
#define AMAZON_FILE "dataset/Amazon0312.txt"

#define ELT_DIRECTED false
#define ELT_FILE "dataset/4elt.graph.txt"

void snap_loader(Graph* graph, const char* file_name, bool directed);

void elt_loader(Graph* graph);

#endif
