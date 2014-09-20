#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

#include"partition.h"

class Graph {
public:
  Graph () : counted_edges_number(0), counted_nodes_number(0) {}

  void add_neighbor(int node_index, int neighbor_index);

  void check_number_edges();

  const std::vector<int>& get_neighbors(int node_index) const;

  void get_nodes_randomly(std::vector<int>* nodes) const;

  void print_graph() const;

  double get_fraction_edges_cut(const Partition& partition) const;

  int get_nodes_number() const {
    return counted_nodes_number;
  }

private:
  int counted_edges_number;
  int counted_nodes_number;
  std::vector<std::vector<int> > neighbors;
};

#endif
