#include"graph.h"
#include"loaders.h"

#include<cstdio>

int main()
{
  Graph slashdot_graph;

  slashdot_loader(&slashdot_graph);
  slashdot_graph.print_graph();

  return 0;
}
