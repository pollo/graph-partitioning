#include"graph.h"
#include"loaders.h"
#include"partition.h"
#include"partitioners.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_PARTITIONS 10000

int main(int argc, char** argv)
{
  Graph graph;
  Partition partition;

  if (argc != 4)
  {
    printf("Invalid number of parameters\n");
    printf("Usage: %s <dataset name> <heuristic name> <partitions number>\n",
           argv[0]);
    exit(1);
  }

  if (strncmp(argv[1],"slashdot",8) == 0)
    snap_loader(&graph, SLASHDOT_FILE, SLASHDOT_DIRECTED);
  else if (strncmp(argv[1],"amazon",6) == 0) {
    snap_loader(&graph, AMAZON_FILE, AMAZON_DIRECTED);
    graph.print_graph();
    return 0;
  }
  else if (strncmp(argv[1],"4elt",4) == 0)
    elt_loader(&graph);
  else
  {
    printf("Invalid dataset name %s\n",argv[1]);
    exit(1);
  }

  int partitions_number = strtol(argv[3], NULL, 10);
  if (partitions_number < 1 || partitions_number > MAX_PARTITIONS)
  {
    printf("Invalid partition number %s\n",argv[3]);
    exit(1);
  }

  if (strncmp(argv[2],"LDG",3) == 0)
  {
    linear_deterministic_greedy(graph,
                                partitions_number,
                                &partition);
  }
  else if (strncmp(argv[2],"FENNEL",6) == 0)
  {
    fennel(graph,
           partitions_number,
           &partition);
  }
  else
  {
    printf("Invalid heuristic name %s\n",argv[2]);
    exit(1);
  }

  double fraction_edges_cut = graph.get_fraction_edges_cut(partition);
  printf("Fraction of edges cut of dataset %s with heuristic "\
         "%s and %d partitions:\n %f\n",
         argv[1],
         argv[2],
         partitions_number,
         fraction_edges_cut);

  return 0;
}
