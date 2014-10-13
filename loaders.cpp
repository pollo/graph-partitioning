#include"loaders.h"

#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<cstdlib>

using namespace std;

void snap_loader(Graph* graph, const char* file_name) {
  int n,m;
  int from, to;
  char buffer[1000];
  FILE *fp = fopen(file_name, "r");

  if (fp == NULL)
  {
    printf("File %s not found\n",file_name);
    exit(1);
  }

  fgets(buffer, sizeof buffer, fp);
  fgets(buffer, sizeof buffer, fp);
  fgets(buffer, sizeof buffer, fp);
  sscanf(buffer, "# Nodes: %d Edges: %d",&n,&m);

  //read edges
  while (fgets(buffer, sizeof buffer, fp) != NULL)
  {
    if (buffer[0] != '#')
    {
      sscanf(buffer, "%d\t%d", &from,&to);
      graph->add_neighbor(from,to);
    }
  }

  //graph->print_graph_size();

  fclose(fp);
}

void preprocessed_loader(Graph* graph, const char* file_name) {
  int n,m;
  int from, to;
  char buffer[1000];
  char pre_file_name[1000];
  strcpy(pre_file_name, file_name);
  strcat(pre_file_name, ".preprocessed");

  printf("%s\n",pre_file_name);

  FILE *fp = fopen(pre_file_name, "r");

  fgets(buffer, sizeof buffer, fp);
  sscanf(buffer, "%d %d\n",&n,&m);

  //read edges
  while (fgets(buffer, sizeof buffer, fp) != NULL)
  {
    sscanf(buffer, "%d %d", &from,&to);
    graph->add_neighbor(from,to);
  }

  graph->print_graph_size();

  fclose(fp);
}

void elt_loader(Graph* graph) {
  int n,m;
  int neighbor;
  string line;
  ifstream elt_file(ELT_FILE);

  elt_file >> n;
  elt_file >> m;

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

  graph->print_graph_size();

  elt_file.close();
}

void twitter_loader(Graph* graph) {
  int from, to;
  char buffer[1000];
  FILE *fp = fopen(TWITTER_FILE, "r");

  //read edges
  while (fgets(buffer, sizeof buffer, fp) != NULL)
  {
      sscanf(buffer, "%d\t%d", &from,&to);
      graph->add_neighbor(from,to);
  }

  graph->print_graph_size();

  fclose(fp);
}
