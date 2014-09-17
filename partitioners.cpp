#include "partitioners.h"

#include <cstdio>
#include <cmath>

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

void fennel(const Graph& graph,
            int partitions_number,
            Partition* partition)
{
  const double alfa = pow(partitions_number, 0.5)*(graph.get_edges_number()
                                   / pow(graph.get_nodes_number(), 3/2.0));
  const double v = 1.1;

  vector<int> nodes;
  vector<double> partition_score(partitions_number);

  //get random sorted nodes
  graph.get_nodes_randomly(&nodes);

  //initialize partitions
  partition->set_size(nodes.size(), partitions_number);

  for (vector<int>::iterator node = nodes.begin();
       node != nodes.end();
       ++node) {

    //initialize partitions score
    for (int i=0; i<partitions_number; i++)
      partition_score[i] = 0;

    //add to partitions score number of neighbors in partition
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

    //subtract to partitions score cost function
    for (int i=0; i<partitions_number; i++)
    {
      int partition_size = partition->get_partition_size(i);
      double c = alfa * (pow(partition_size+1, gamma) - pow(partition_size, gamma));
      partition_score[i] -= c;
    }

    //filter out partition above treshold
    vector<pair<double,int> > filtered_partition_score;
    for (int i=0; i<partitions_number; i++)
    {
      if (partition->get_partition_size(i) <=
          v * graph.get_nodes_number() / ((double)partitions_number))
      {
        filtered_partition_score.push_back(pair<double, int>(partition_score[i],
                                                             i));
      }
    }

    //select best partition
    int selected_partition = filtered_partition_score[0].second;
    double score = filtered_partition_score[0].first;
    for (size_t i=1; i<filtered_partition_score.size(); i++)
    {
      if (filtered_partition_score[i].first > score )
      {
        selected_partition = filtered_partition_score[i].second;
        score = filtered_partition_score[i].first;
      }
    }

    //assign node to partition
    partition->set_node_partition(*node, selected_partition);
  }
}

