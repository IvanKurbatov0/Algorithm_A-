#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <math.h>
static int CurrentMem = 0;
static int MaxMem = 0;
class Graph
{
public:
	double** adjList;
	int countNodes;
	int** coordinates;
	Graph randgraph();
	Graph();
	Graph(const Graph&);
	Graph& operator=(const Graph&);
	~Graph();
	Graph(int);
	void add(int, int, double);
};
#endif 