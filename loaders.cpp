#include"loaders.h"

#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

void slashdot_loader(Graph* graph) {
  int from, to;
  char buffer[1000];
  FILE *slashdot_fp = fopen(SLASHDOT_FILE, "r");

  graph->initialize(SLASHDOT_NODES, SLASHDOT_EDGES, SLASHDOT_DIRECTED);

  //read edges
  while (fgets(buffer, sizeof buffer, slashdot_fp) != NULL)
  {
    if (buffer[0] != '#')
    {
      sscanf(buffer, "%d\t%d", &from,&to);
      graph->add_neighbor(from,to);
    }
  }

  fclose(slashdot_fp);
}

void elt_loader(Graph* graph) {
  int n,m;
  int neighbor;
  string line;
  ifstream elt_file(ELT_FILE);

  elt_file >> n;
  elt_file >> m;

  graph->initialize(n, m, ELT_DIRECTED);

  //read edges
  getline(elt_file, line);
  for (int i=0 ; i<n; i++)
  {
    getline(elt_file, line);
    stringstream linestream(line);

    while (linestream >> neighbor)
    {
      neighbor--;
      graph->add_neighbor(i, neighbor);
    }
  }

  elt_file.close();
}
