#include"loaders.h"

#include<cstdio>

void slashdot_loader(Graph* slashdot_graph) {
  int from, to;
  FILE *slashdot_fp = fopen(SLASHDOT_FILE, "r");

  slashdot_graph->set_size(SLASHDOT_SIZE);

  //read edges
  while (fscanf(slashdot_fp, "%d\t%d", &from,&to)) {
    slashdot_graph->add_neighbor(from,to);
  }

  fclose(slashdot_fp);
}


