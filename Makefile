CC=g++

#debug
FLAGS=-Wall
#no debug
#FLAGS= -O3

all: graph_partitioning

graph_partitioning: graph_partitioning.cpp graph.o loaders.o
	$(CC) $(FLAGS) graph_partitioning.cpp graph.o loaders.o -o graph_partitioning

graph.o: graph.cpp graph.h
	$(CC) $(FLAGS) -c graph.cpp

loaders.o: loaders.cpp loaders.h
	$(CC) $(FLAGS) -c loaders.cpp

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*~" | xargs rm -f
	rm graph_partitioning

.PHONY: clean
