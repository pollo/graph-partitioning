#ifndef LOADERS_H
#define LOADERS_H

#include "graph.h"

#define SLASHDOT_DIRECTED true
#define SLASHDOT_FILE "dataset/soc-Slashdot0811.txt"

#define AMAZON_DIRECTED true
#define AMAZON_FILE "dataset/Amazon0312.txt"

#define ELT_DIRECTED false
#define ELT_FILE "dataset/4elt.graph.txt"

#define TWITTER_DIRECTED true
#define TWITTER_FILE "dataset/twitter_rv.net"

#define LIVEJOURNAL_DIRECTED true
#define LIVEJOURNAL_FILE "dataset/soc-LiveJournal1.txt"

#define FACEBOOK_DIRECTED false
#define FACEBOOK_FILE "dataset/facebook_combined.txt"

void snap_loader(Graph* graph, const char* file_name);

void preprocessed_loader(Graph* graph, const char* file_name);

void elt_loader(Graph* graph);

void twitter_loader(Graph* graph);

#endif
