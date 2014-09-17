#ifndef PARTITIONERS_H
#define PARTITIONERS_H

#include "graph.h"
#include "partition.h"

void linear_deterministic_greedy(const Graph& graph,
                                 int partitions_number,
                                 Partition* partition);

void fennel(const Graph& graph,
            int partitions_number,
            Partition* partition);

#endif
