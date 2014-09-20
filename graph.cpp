#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cassert>

#include"graph.h"

using namespace std;

void Graph::add_neighbor(int node_index, int neighbor_index)
{
  if (node_index != neighbor_index)
  {
    if (node_index>=counted_nodes_number ||
        neighbor_index>=counted_nodes_number)
    {
      counted_nodes_number = max(node_index, neighbor_index) + 1;
      neighbors.resize(max(counted_nodes_number, (int) neighbors.size()));
    }

    if (find(neighbors[node_index].begin(),
             neighbors[node_index].end(),
             neighbor_index) == neighbors[node_index].end())
    {
      assert(find(neighbors[neighbor_index].begin(),
                  neighbors[neighbor_index].end(),
                  node_index) == neighbors[neighbor_index].end());
      neighbors[node_index].push_back(neighbor_index);
      neighbors[neighbor_index].push_back(node_index);
      counted_edges_number += 1;
    }
  }
}

void Graph::print_graph_size() const {
  printf("Counted number of edges %lld\n", counted_edges_number);
  printf("Counted number of nodes %d\n", counted_nodes_number);
}

void Graph::print_graph() const
{
/*  for (int i=0; i<nodes_number; i++)
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
    }*/
  printf("%d %lld\n",counted_nodes_number, counted_edges_number);
  for (int i=0; i<counted_nodes_number; i++)
  {
    const vector<int>& neighbors = get_neighbors(i);
    bool no = true;
    for (vector<int>::const_iterator it = neighbors.begin();
         it != neighbors.end();
         it++)
    {
      no = false;
      printf("%d ",*it+1);
    }
    if (no)
      printf("%d ",i+1);
    printf("\n");
  }
}

const vector<int>& Graph::get_neighbors(int node_index) const {
  return neighbors[node_index];
}

int myrandom (int i) { return std::rand()%i;}

void Graph::get_nodes_randomly(vector<int>* nodes) const {
  srand ( unsigned ( std::time(0) ) );
  nodes->resize(counted_nodes_number);
  for (int i=0; i<counted_nodes_number; i++)
    (*nodes)[i] = i;
  random_shuffle(nodes->begin(), nodes->end(), myrandom);
}

double Graph::get_fraction_edges_cut(const Partition& partition) const {
  long long int edges_cut = 0;

  for (int node = 0; node < counted_nodes_number; node++)
  {
    int node_partition = partition.get_node_partition(node);
    for (vector<int>::const_iterator neighbor = neighbors[node].begin();
         neighbor != neighbors[node].end();
         ++neighbor)
    {
      if (node_partition != partition.get_node_partition(*neighbor))
        edges_cut++;
    }
  }

  edges_cut /= 2;

  return ((double) edges_cut)/counted_edges_number;
}

double Graph::get_normalized_maximum_load(const Partition& partition) const {
  int maximum_load = 0;

  for (int i=0; i<partition.get_partitions_number(); i++)
  {
    int partition_size = partition.get_partition_size(i);
    if (partition_size > maximum_load)
      maximum_load = partition_size;
  }

  return maximum_load / \
    ((double) counted_nodes_number / partition.get_partitions_number());
}
