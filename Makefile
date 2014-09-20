CC=g++

#debug
FLAGS=-Wall -O3
#no debug
#FLAGS= -O3

all: graph_partitioning

graph_partitioning: graph_partitioning.cpp graph.o loaders.o partition.o partitioners.o
	$(CC) $(FLAGS) graph_partitioning.cpp graph.o loaders.o partition.o partitioners.o -o graph_partitioning

graph.o: graph.cpp graph.h
	$(CC) $(FLAGS) -c graph.cpp

loaders.o: loaders.cpp loaders.h
	$(CC) $(FLAGS) -c loaders.cpp

partition.o: partition.cpp partition.h
	$(CC) $(FLAGS) -c partition.cpp

partitioners.o: partitioners.cpp partitioners.h
	$(CC) $(FLAGS) -c partitioners.cpp

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*~" | xargs rm -f
	rm graph_partitioning

.PHONY: clean
