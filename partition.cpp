#include"partition.h"

using namespace std;

void Partition::set_size(int nodes_number, int partitions_number)
{
  this->nodes_number = nodes_number;
  //-1 means not yet assigned
  partitions.resize(nodes_number, -1);
  partition_sizes.resize(partitions_number, 0);
}

void Partition::set_node_partition(int node_index, int partition)
{
  partitions[node_index] = partition;
  partition_sizes[partition]++;
}

int Partition::get_node_partition(int node_index) const
{
  return partitions[node_index];
}

int Partition::get_partition_size(int partition_index) const
{
  return partition_sizes[partition_index];
}
