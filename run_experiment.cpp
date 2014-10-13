#include"graph.h"
#include"loaders.h"
#include"partition.h"
#include"partitioners.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAX_PARTITIONS 10000
#define N_EXPERIMENTS 10

void run_heuristic(const char* heuristic_name,
                   int partitions_number,
                   const char* dataset,
                   const Graph& graph)
{
  Partition partition;

}

int main(int argc, char** argv)
{
  Graph graph;

  if (argc != 2)
  {
    printf("Invalid number of parameters\n");
    printf("Usage: %s <dataset file>\n",
           argv[0]);
    exit(1);
  }

  snap_loader(&graph, argv[1]);

  printf("Dataset;Experiment #;Heuristic;K;Edge cut;"\
         "Communication Volume; Normalized Maximum Load;Runtime\n");
  for (int experiment = 1; experiment<=N_EXPERIMENTS; experiment++)
  {
    for (int heuristic = 0; heuristic<3; heuristic++)
    {
      for (int partitions_number = 2;
           partitions_number<=1024;
           partitions_number *= 2)
      {
        Partition partition;
        time_t start = time(0);
        const char* h_name;

        if (heuristic == 0)
        {
          linear_deterministic_greedy(graph,
                                      partitions_number,
                                      &partition);
          h_name = "LDG";
        }
        else if (heuristic == 1)
        {
          fennel(graph,
                 partitions_number,
                 &partition);
          h_name = "FENNEL";
        }
        else
        {
          non_neighbors_greedy(graph,
                               partitions_number,
                               &partition);
          h_name = "NNEIGHBORS";
        }
        time_t end = time(0);
        int time = difftime(end, start);

        double fraction_edges_cut = graph.get_fraction_edges_cut(partition);
        double communication_volume = graph.get_communication_volume(partition);
        double maximum_load = graph.get_normalized_maximum_load(partition);

        printf("%s;%d;%s;%d;%lf;%lf;%lf;%d\n",
               argv[1], experiment, h_name, partitions_number,
               fraction_edges_cut, communication_volume, maximum_load, time);

      }
    }
  }


  return 0;
}
