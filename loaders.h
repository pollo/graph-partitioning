#ifndef LOADERS_H
#define LOADERS_H

#include "graph.h"

#define SLASHDOT_NODES 77360
#define SLASHDOT_EDGES 905468
#define SLASHDOT_DIRECTED true
#define SLASHDOT_FILE "dataset/soc-Slashdot0811.txt"

#define ELT_DIRECTED false
#define ELT_FILE "dataset/4elt.graph.txt"

void slashdot_loader(Graph* graph);

void elt_loader(Graph* graph);

#endif
