#include"loaders.h"

#include<cstdio>

void slashdot_loader(Graph* slashdot_graph) {
  int from, to;
  char buffer[1000];
  FILE *slashdot_fp = fopen(SLASHDOT_FILE, "r");

  slashdot_graph->initialize(SLASHDOT_SIZE, SLASHDOT_DIRECTED);

  //read edges
  while (fgets(buffer, sizeof buffer, slashdot_fp) != NULL)
  {
    if (buffer[0] != '#')
    {
      sscanf(buffer, "%d\t%d", &from,&to);
      slashdot_graph->add_neighbor(from,to);
    }
  }

  fclose(slashdot_fp);
}


