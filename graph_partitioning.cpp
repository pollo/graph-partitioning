#include"graph.h"
#include"loaders.h"
#include"partition.h"
#include"partitioners.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAX_PARTITIONS 10000

void run_heuristic(const char* heuristic_name,
                   int partitions_number,
                   const char* dataset,
                   const Graph& graph)
{
  Partition partition;

  time_t start = time(0);
  if (strncmp(heuristic_name,"LDG",3) == 0)
  {
    linear_deterministic_greedy(graph,
				partitions_number,
                                &partition);
  }
  else if (strncmp(heuristic_name,"FENNEL",6) == 0)
  {
    fennel(graph,
           partitions_number,
           &partition);
  }
  else if (strncmp(heuristic_name,"NNEIGHBORS",10) == 0)
  {
    non_neighbors_greedy(graph,
                         partitions_number,
                         &partition);
  }
  else
  {
    printf("Invalid heuristic name %s\n",heuristic_name);
    exit(1);
  }

  time_t end = time(0);
  int time = difftime(end, start);
  printf("Partitioned in %d seconds\n",time);

  double fraction_edges_cut = graph.get_fraction_edges_cut(partition);
  double communication_volume = graph.get_communication_volume(partition);
  double maximum_load = graph.get_normalized_maximum_load(partition);
  printf("Dataset %s with heuristic %s and %d partitions:\n",
         dataset,
         heuristic_name,
         partitions_number);
  printf("Fraction edges cut = %f\nNormalized maximum load = %f\n",
         fraction_edges_cut,
         maximum_load);
  printf("Communication volume %f\n\n",
         communication_volume);
}

int main(int argc, char** argv)
{
  Graph graph;

  if (argc != 4)
  {
    printf("Invalid number of parameters\n");
    printf("Usage: %s <dataset name> <heuristic names> <partitions number>\n",
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
  else if (strncmp(argv[1],"pre.amazon",11) == 0) {
    preprocessed_loader(&graph, AMAZON_FILE);
  }
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

  bool heuristics_valid = false;
  if (strstr(argv[2],"LDG") != NULL)
  {
    run_heuristic("LDG",partitions_number,argv[1],graph);
    heuristics_valid = true;
  }

  if (strstr(argv[2],"FENNEL") != NULL)
  {
    run_heuristic("FENNEL",partitions_number,argv[1],graph);
    heuristics_valid = true;
  }

  if (strstr(argv[2],"NNEIGHBORS") != NULL)
  {
    run_heuristic("NNEIGHBORS",partitions_number,argv[1],graph);
    heuristics_valid = true;
  }

  if (!heuristics_valid)
  {
    printf("Invalid heuristic name %s\n",argv[2]);
    exit(1);
  }

  return 0;
}
