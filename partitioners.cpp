#include "partitioners.h"

#include <cstdio>

using namespace std;

void linear_deterministic_greedy(const Graph& graph,
                                 int partitions_number,
                                 Partition* partition)
{
  vector<int> nodes;
  vector<double> partition_score(partitions_number);

  //get random sorted nodes
  graph.get_nodes_randomly(&nodes);

  //initialize partitions
  partition->set_size(nodes.size(), partitions_number);

  for (vector<int>::iterator node = nodes.begin();
       node != nodes.end();
       ++node) {
    printf("Considering node %d\n",*node);

    //initialize partitions score
    for (int i=0; i<partitions_number; i++)
      partition_score[i] = 0;

    //compute partitions score
    for (vector<int>::const_iterator neighbor =
           graph.get_neighbors(*node).begin();
         neighbor != graph.get_neighbors(*node).end();
         ++neighbor)
    {
      int neighbor_partition = partition->get_node_partition(*neighbor);
      if (neighbor_partition >= 0) {
        partition_score[neighbor_partition]++;
      }
    }

    //weight partitions score
    for (int i=0; i<partitions_number; i++)
    {
      double C = ((double)nodes.size())/partitions_number;
      partition_score[i] *= 1 - partition->get_partition_size(i)/C;
    }

    //select best partition
    int selected_partition = -1;
    double score = 0;
    for (int i=0; i<partitions_number; i++)
    {
      if (partition_score[i] > score)
      {
        selected_partition = i;
        score = partition_score[i];
      }
      else if (partition_score[i] == score)
      {
        if (selected_partition == -1 ||
            partition->get_partition_size(i) <=
            partition->get_partition_size(selected_partition))
        {
          selected_partition = i;
        }
      }
    }

    //assign node to partition
    partition->set_node_partition(*node, selected_partition);
  }
}
