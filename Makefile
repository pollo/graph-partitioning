CC=g++

#debug
FLAGS=-Wall -O3
#no debug
#FLAGS= -O3

all: graph_partitioning preprocessing run_experiment

graph_partitioning: graph_partitioning.cpp graph.o loaders.o partition.o partitioners.o
	$(CC) $(FLAGS) graph_partitioning.cpp graph.o loaders.o partition.o partitioners.o -o graph_partitioning

preprocessing: preprocessing.cpp graph.o loaders.o
	$(CC) $(FLAGS) preprocessing.cpp graph.o loaders.o partition.o -o preprocessing

run_experiment: run_experiment.cpp graph.o loaders.o partition.o partitioners.o
	$(CC) $(FLAGS) run_experiment.cpp graph.o loaders.o partition.o partitioners.o -o run_experiment

graph.o: graph.cpp graph.h partition.o
	$(CC) $(FLAGS) -c graph.cpp

loaders.o: loaders.cpp loaders.h graph.o
	$(CC) $(FLAGS) -c loaders.cpp

partition.o: partition.cpp partition.h
	$(CC) $(FLAGS) -c partition.cpp

partitioners.o: partitioners.cpp partitioners.h graph.o partition.o
	$(CC) $(FLAGS) -c partitioners.cpp

clean:
	find . -name "*.o" | xargs rm -f
	find . -name "*~" | xargs rm -f
	rm graph_partitioning run_experiment

.PHONY: clean
