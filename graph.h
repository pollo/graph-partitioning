#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

#include"partition.h"

class Graph {
public:
  void initialize(int nodes_number, bool directed);

  void add_neighbor(int node_index, int neighbor_index);

  const std::vector<int>& get_neighbors(int node_index) const;

  void get_nodes_randomly(std::vector<int>* nodes) const;

  void print_graph() const;

  double get_fraction_edges_cut(const Partition& partition) const;

private:
  int nodes_number;
  bool directed;
  std::vector<std::vector<int> > neighbors;
};

#endif
