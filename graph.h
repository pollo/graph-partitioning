#ifndef GRAPH_H
#define GRAPH_H

#include<vector>

class Graph {
public:
  void set_size(int nodes_number);

  void add_neighbor(int node_index, int neighbor_index);

  const std::vector<int>& get_neighbors(int node_index);

  void print_graph();

private:
  int nodes_number;

  std::vector<std::vector<int> > neighbors;
};

#endif
