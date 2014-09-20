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
    snap_loader(&graph, SLASHDOT_FILE);
  else if (strncmp(argv[1],"amazon",6) == 0) {
    snap_loader(&graph, AMAZON_FILE);
  }
  else if (strncmp(argv[1],"4elt",4) == 0)
    elt_loader(&graph);
  else if (strncmp(argv[1],"twitter",7) == 0)
    twitter_loader(&graph);
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
  double maximum_load = graph.get_normalized_maximum_load(partition);
  printf("Dataset %s with heuristic %s and %d partitions:\n",
         argv[1],
         argv[2],
         partitions_number);
  printf("Fraction edges cut = %f\nNormalized maximum load = %f\n",
         fraction_edges_cut,
         maximum_load);

  return 0;
}
