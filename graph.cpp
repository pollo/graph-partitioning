#include <cstdio>
#include <algorithm>

#include"graph.h"

using namespace std;

void Graph::initialize(int nodes_number, bool directed)
{
  this->nodes_number = nodes_number;
  this->directed = directed;
  neighbors.resize(nodes_number);
}

void Graph::add_neighbor(int node_index, int neighbor_index)
{
  neighbors[node_index].push_back(neighbor_index);
}

void Graph::print_graph() const
{
  for (int i=0; i<nodes_number; i++)
  {
    printf("Node %d has neighbors: ",i);
    const vector<int>& neighbors = get_neighbors(i);
    for (vector<int>::const_iterator it = neighbors.begin();
         it != neighbors.end();
         it++)
    {
      printf("%d ",*it);
    }
    printf("\n");
  }
}

const vector<int>& Graph::get_neighbors(int node_index) const {
  return neighbors[node_index];
}

void Graph::get_nodes_randomly(vector<int>* nodes) const {
  nodes->resize(nodes_number);
  for (int i=0; i<nodes_number; i++)
    (*nodes)[i] = i;
  random_shuffle(nodes->begin(), nodes->end());
}

double Graph::get_fraction_edges_cut(const Partition& partition) const {
  int edges_cut = 0;
  int tot_edges = 0;

  for (size_t node = 0; node < nodes_number; node++)
  {
    int node_partition = partition.get_node_partition(node);
    for (vector<int>::const_iterator neighbor = neighbors[node].begin();
         neighbor != neighbors[node].end();
         ++neighbor)
    {
      tot_edges += 1;
      if (node_partition != partition.get_node_partition(*neighbor))
        edges_cut++;
    }
  }

  if (!this->directed)
  {
    edges_cut /= 2;
    tot_edges /= 2;
  }

  return ((double) edges_cut)/tot_edges;
}
