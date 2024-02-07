#include "Graph.h"

Graph::Graph()
{
	adjList = nullptr;
	coordinates = nullptr;
	countNodes = 0;
}
Graph::Graph(int nodes)
{
	adjList = new double* [nodes];
	coordinates = new int* [nodes];
	CurrentMem += sizeof(double*) * nodes+sizeof(int*) * nodes;
	for (int i = 0; i < nodes; i++)
	{
		adjList[i] = new double[nodes] {0};
		coordinates[i] = new int[2] {0};
		CurrentMem += sizeof(double) * nodes+sizeof(int) * 2;
	}
	countNodes = nodes;
	if (MaxMem < CurrentMem)
	{
		MaxMem = CurrentMem;
	}
}
Graph::Graph(const Graph& g)
{
	if (this != &g)
	{
		countNodes = g.countNodes;
		adjList = new double* [countNodes];
		coordinates = new int* [countNodes];
		CurrentMem += sizeof(double*) * countNodes + sizeof(int*) * countNodes;
		for (int i = 0; i < countNodes; i++)
		{
			adjList[i] = new double[countNodes] {0};
			coordinates[i] = new int[2] {0};
			CurrentMem += sizeof(double) * countNodes + sizeof(int) * 2;
			for (int j = 0; j < countNodes; j++)
			{
				adjList[i][j] = g.adjList[i][j];
			}
			for (int j = 0; j < 2; j++)
			{
				coordinates[i][j] = g.coordinates[i][j];
			}
		}
		if (MaxMem < CurrentMem)
		{
			MaxMem = CurrentMem;
		}
	}
}
Graph& Graph::operator=(const Graph& g)
{
	if (this != &g)
	{
		this->~Graph();
		countNodes = g.countNodes;
		adjList = new double* [countNodes];
		coordinates = new int* [countNodes];
		CurrentMem += sizeof(double*) * countNodes+sizeof(int*)*countNodes;
		for (int i = 0; i < countNodes; i++)
		{
			adjList[i] = new double[countNodes] {0};
			coordinates[i] = new int[2] {0};
			CurrentMem += sizeof(double*) * countNodes + sizeof(int*) * 2;
			for (int j = 0; j < countNodes; j++)
			{
				adjList[i][j] = g.adjList[i][j];
			}
			for (int j = 0; j < 2; j++)
			{
				coordinates[i][j] = g.coordinates[i][j];
			}
		}
		if (MaxMem < CurrentMem)
		{
			MaxMem = CurrentMem;
		}
	}
	return *this;
}
Graph::~Graph()
{
	for (int i = 0; i < countNodes; i++)
	{
		delete[] adjList[i];
		delete[] coordinates[i];
		CurrentMem -= sizeof(double) * countNodes;
		CurrentMem -= sizeof(int) * 2;
	}
	delete[] adjList;
	delete[] coordinates;
	CurrentMem -= sizeof(double*) * countNodes;
	CurrentMem -= sizeof(int*) * 2;
}
void Graph::add(int u, int v, double cost)
{
	adjList[u][v] = cost;
	adjList[v][u] = cost;
}
Graph Graph::randgraph()
{
	int max_coord = 1000;
	bool flag3 = false;
	do{
		for (int i = 0; i < countNodes; i++)
		{
			for (int j = 0; j < countNodes; j++)
			{
				adjList[i][j] = 0;
			}
		}
		int k = 0;
		do {
			bool flag1 = true;
			int coord_x = rand() % max_coord;
			int coord_y = rand() % max_coord;
			for (int i = 0; i < countNodes; i++)
			{
				if (coordinates[i][0] == coord_x && coordinates[i][1] == coord_y)
				{
					flag1 = false;
					break;
				}
			}
			if (flag1)
			{
				coordinates[k][0] = coord_x;
				coordinates[k][1] = coord_y;
				k++;
			}
		} while (k < countNodes);
		int count_edge;
		if (countNodes == 1) count_edge = 0;
		else if (countNodes == 2) count_edge = 1;
		else
		{
			do {
				count_edge = 1 + rand() % (3 * countNodes - 6);
			} while (count_edge < countNodes - 1);
		}
		int node1, node2;
		for (int i = 0; i < count_edge; i++)
		{
			bool flag2 = true;
			do {
				do
				{
					node1 = rand() % countNodes;
					node2 = rand() % countNodes;
				} while (adjList[node1][node2] != 0 || node1 == node2);
				int ab_x = coordinates[node1][0] - coordinates[node2][0];
				int ab_y = coordinates[node1][1] - coordinates[node2][1];
				for (int i = 0; i < countNodes; i++)
				{
					for (int j = 0; j < countNodes; j++)
					{
						if (this->adjList[i][j] != 0 && ((i != node1 && j != node2) || (i != node2 && j != node1)))
						{
							int ac_x = coordinates[node1][0] - coordinates[i][0];
							int ac_y = coordinates[node1][1] - coordinates[i][1];
							int ad_x = coordinates[node1][0] - coordinates[j][0];
							int ad_y = coordinates[node1][1] - coordinates[j][1];
							if (((ab_x * ac_y - ab_y * ac_x) > 0) && ((ab_x * ad_y - ab_y * ad_x) < 0) || (ab_x * ac_y - ab_y * ac_x) < 0 && (ab_x * ad_y - ab_y * ad_x) > 0)
							{
								flag2 = false;
								break;
							}
							int cd_x = coordinates[j][0] - coordinates[i][0];
							int cd_y = coordinates[j][1] - coordinates[i][1];
							int cb_x = coordinates[node2][0] - coordinates[i][0];
							int cb_y = coordinates[node2][1] - coordinates[i][1];
							int ca_x = coordinates[node1][0] - coordinates[i][0];
							int ca_y = coordinates[node1][1] - coordinates[i][1];
							if (((cd_x * cb_y - cd_y * cb_x) > 0) && ((cd_x * ca_y - cd_y * ca_x) < 0) || (cd_x * cb_y - cd_y * cb_x) < 0 && (cd_x * ca_y - cd_y * ca_x) > 0)
							{
								flag2 = false;
								break;
							}
							else {
								flag2 = true;
								break;
							}
						}
					}
					break;
				}
			} while (!flag2);
			add(node1, node2, sqrt(pow(coordinates[node1][0] - coordinates[node2][0], 2) + pow(coordinates[node1][1] - coordinates[node2][1], 2)));
		}
		for (int i = 0; i < countNodes; i++)
		{
			flag3 = true;
			for (int j = 0; j < countNodes; j++)
			{
				if (adjList[i][j] != 0)
				{
					flag3 = false;
					break;
				}
			}
			if (flag3) break;
		}
	} while (flag3);
	return *this;
}











