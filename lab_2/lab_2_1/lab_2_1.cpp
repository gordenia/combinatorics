#include "stdafx.h"

const size_t maxCountVertex = 10;
typedef std::array<std::array<size_t, maxCountVertex>, maxCountVertex> Graph;

Graph BuildGraph(std::ifstream &inputFile, size_t &countVertex)
{
	size_t countEdge;
	size_t v1, v2;
	inputFile >> countVertex;
	inputFile >> countEdge;

	Graph inputGraph;

	for (size_t i = 0; i < maxCountVertex; ++i)
		for (size_t j = 0; j < maxCountVertex; ++j)
			inputGraph[i][j] = 0;

	for (size_t i = 0; i < countEdge; ++i)
	{
		inputFile >> v1;
		inputFile >> v2;

		inputGraph[v1-1][v2-1] = 1;
		inputGraph[v2-1][v1-1] = 1;
	}

	return inputGraph;
}

void PrintGraph(const Graph &graph, const size_t countVertex)
{
	std::cout << "Input graph:" << std::endl;

	for (size_t i = 0; i < countVertex; ++i)
	{
		for (size_t j = 0; j < countVertex; ++j)
		{
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Search(size_t v, std::vector<bool> &used, size_t timer, std::vector<size_t> &tIn, std::vector<size_t> &tOut, const Graph &graph, std::vector<size_t> &degree, int p = -1)
{
	used[v] = true;
	int to;
	tIn[v] = tOut[v] = timer++;
	for (size_t i = 0 ; i < used.size(); ++i)
	{
		if (graph[v][i] == 1)
		{
			degree[v]++;
			to = i;

			if (to == p) continue;

			if (used[to])
				tOut[v] = std::min(tOut[v], tIn[to]);
			else
			{
				Search(to, used, timer, tIn, tOut, graph, degree, v);
				tOut[v] = std::min(tOut[v], tOut[to]);

				if (tOut[to] > tIn[v]) 
				{
					if (degree[v] > 1)
					{
						std::cout << "\nJunction points:" << std::endl;
						std::cout << v + 1 << std::endl;
					}

					if (degree[to] > 1)
					{
						std::cout << "\nJunction points:" << std::endl;
						std::cout << to + 1 << std::endl;
					}
					
					std::cout << "Bridges:" << std::endl;
					std::cout << v + 1 << "-" << to + 1 << std::endl;
				}
			}
		}
	}
}


void FindBridges(const Graph &graph, const size_t countVertex)
{
	std::vector<size_t> tIn(countVertex, 0), tOut(countVertex, 0);
	std::vector<bool> used(countVertex, false);
	std::vector<size_t> degree(countVertex, 0);
	size_t timer = 0;

	for (size_t i = 0; i < countVertex; ++i)
		if (!used[i])
			Search(i, used, timer, tIn, tOut, graph, degree);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid count arguments" << std::endl;
		return 1;
	}

	std::ifstream inputFile;
	Graph graph;
	size_t countVertex;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	graph = BuildGraph(inputFile, countVertex);
	PrintGraph(graph, countVertex);
	FindBridges(graph, countVertex);
	return 0;
}

