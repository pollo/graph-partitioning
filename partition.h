#ifndef PARTITION_H
#define PARTITION_H

#include<vector>

class Partition {
public:
  void set_size(int nodes_number, int partitions_number);

  void set_node_partition(int node_index, int partition);

  int get_node_partition(int node_index) const;

  int get_partition_size(int partition_index) const;

private:
  int nodes_number;

  std::vector<int> partitions;
  std::vector<int> partition_sizes;
};

#endif
