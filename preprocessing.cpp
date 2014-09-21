#include"graph.h"
#include"loaders.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int dfs(int node,
        int component_id,
        vector<int>& component,
        const Graph& graph)
{
  component[node] = component_id;
  int discovered = 1;
  for (size_t j = 0;
       j < graph.get_neighbors(node).size();
       j++)
  {
    int neighbor = graph.get_neighbors(node)[j];
    if (component[neighbor] == -1)
      discovered += dfs(neighbor, component_id, component, graph);
  }

  return discovered;
}

int find_largest_component(vector<int>& component,
                           const Graph& graph) {
  component.resize(graph.get_nodes_number(), -1);
  int largest_component = -1;
  int largest_size = 0;
  int component_id = 1;
  for (int i=0; i<graph.get_nodes_number(); i++)
  {
    if (component[i] == -1)
    {
      int component_size = dfs(i, component_id, component, graph);
      if (component_size > largest_size)
      {
        largest_size = component_size;
        largest_component = component_id;
      }
      component_id ++;
    }
  }

  return largest_component;
}

void count_nodes_edges(int component_id,
                      const vector<int>& component,
                      const Graph& graph,
                      int* n,
                      int *m)
{
  int nodes = 0, edges = 0;

  for (size_t i=0; i<component.size(); i++)
  {
    if (component[i] == component_id)
    {
      nodes ++;
      edges += graph.get_neighbors(i).size();
    }
  }

  edges /= 2.0;

  *n = nodes;
  *m = edges;
}

int main(int argc, char** argv)
{
  Graph graph;

  if (argc != 2)
  {
    printf("Invalid number of parameters\n");
    printf("Usage: %s <dataset name>\n",
           argv[0]);
    exit(1);
  }

  char output_name[1000];
  if (strncmp(argv[1],"slashdot",8) == 0)
  {
    snap_loader(&graph, SLASHDOT_FILE);
    strcpy(output_name, SLASHDOT_FILE);
  }
  else if (strncmp(argv[1],"amazon",6) == 0)
  {
    snap_loader(&graph, AMAZON_FILE);
    strcpy(output_name, AMAZON_FILE);
  }
  else if (strncmp(argv[1],"4elt",4) == 0)
  {
    elt_loader(&graph);
    strcpy(output_name, ELT_FILE);
  }
  else if (strncmp(argv[1],"twitter",7) == 0)
  {
    twitter_loader(&graph);
    strcpy(output_name, TWITTER_FILE);
  }
  else
  {
    printf("Invalid dataset name %s\n",argv[1]);
    exit(1);
  }
  strcat(output_name, ".preprocessed");

  vector<int> component;
  int largest_component = find_largest_component(component, graph);

  int n,m;
  count_nodes_edges(largest_component, component, graph, &n, &m);;

  printf("Nodes %d, edges %d\n",n,m);

  //assign new id
  vector<int> remap(component.size(), -1);
  int node_id = 0;
  for (size_t i=0; i<component.size(); i++)
  {
    if (component[i] == largest_component)
    {
      remap[i] = node_id;
      node_id ++;
    }
  }

  FILE *fp = fopen(output_name, "w");
  fprintf(fp, "%d %d\n",n,m*2);
  for (size_t i=0; i<component.size(); i++)
  {
    if (component[i] == largest_component)
    {
      for (size_t j=0; j<graph.get_neighbors(i).size(); j++)
      {
        int neighbor = graph.get_neighbors(i)[j];
        fprintf(fp, "%d %d\n",remap[i],remap[neighbor]);
      }
    }
  }

  fclose(fp);
  return 0;
}
