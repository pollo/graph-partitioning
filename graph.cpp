#include <cstdio>

#include"graph.h"

using namespace std;

void Graph::set_size(int nodes_number)
{
  this->nodes_number = nodes_number;
  neighbors.resize(nodes_number);
}

void Graph::add_neighbor(int node_index, int neighbor_index)
{
  neighbors[node_index].push_back(neighbor_index);
}

void Graph::print_graph()
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

const vector<int>& Graph::get_neighbors(int node_index) {
  return neighbors[node_index];
}

