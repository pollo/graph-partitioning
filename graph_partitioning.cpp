#include"graph.h"
#include"loaders.h"
#include"partition.h"
#include"partitioners.h"

#include<cstdio>

int main()
{
  Graph slashdot_graph;
  Partition partition;

  slashdot_loader(&slashdot_graph);
  //slashdot_graph.print_graph();

  linear_deterministic_greedy(slashdot_graph,
                              4,
                              &partition);

  printf("Fraction of edges cut: %d\n",
         slashdot_graph.get_fraction_edges_cut(partition));

  return 0;
}
