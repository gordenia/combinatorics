// lab_2_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <ostream>
#include <vector>

typedef std::vector<std::vector<int>> Graph;

void BuildGraph(std::ifstream &inputFile, Graph &graph, Graph &invertGraph)
{
	size_t countVertex;
	inputFile >> countVertex;
	graph.resize(countVertex);
	invertGraph.resize(countVertex);

	for (size_t i = 0; i < countVertex; ++i)
	{
		graph[i].resize(countVertex);

		for (size_t j = 0; j < countVertex; ++j)
		{
			invertGraph[j].resize(countVertex);
			inputFile >> graph[i][j];
			invertGraph[j][i] = graph[i][j];
		}
	}

}

void PrintGraph(const Graph &graph)
{
	for (size_t i = 0; i < graph.size(); ++i)
	{
		for (size_t j = 0; j < graph[i].size(); ++j)
		{
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void DfsGraph(size_t v, std::vector<bool> &used, std::vector<size_t> &tOut, const Graph &graph)
{
	used[v] = true;
	for (size_t i = 0; i < graph[v].size(); ++i)
	{
		if (!used[i] && graph[v][i] != 0)
		{
			DfsGraph(i, used, tOut, graph);
		}
	}

	tOut.push_back(v);
}


void DfsInvertGraph(size_t v, std::vector<bool> &used, std::vector<size_t> &tIn, const Graph &invertGraph)
{
	used[v] = true;
	tIn.push_back(v);

	for (size_t i = 0; i < invertGraph[v].size(); ++i)
	{
		if (!used[i] && invertGraph[v][i] != 0)
		{
			DfsInvertGraph(i, used, tIn, invertGraph);
		}
	}

}

size_t SearchComponent(const Graph &graph, const Graph &invertGraph)
{
	std::vector<size_t> tOut, tIn;
	std::vector<bool> used(graph.size(), false);
	size_t countComponent = 0;

	for (size_t i = 0; i < graph.size(); ++i)
		if (!used[i])
			DfsGraph(i, used, tOut, graph);

	used.assign(used.size(), false);

	for (size_t i = 0; i < graph.size(); ++i)
	{
		int v = tOut[graph.size() - 1 - i];
		if (!used[v]) 
		{
			DfsInvertGraph(v, used, tIn, invertGraph);
			countComponent++;
		}
	}

	return countComponent;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid count arguments" << std::endl;
		return 1;
	}

	std::ifstream inputFile;
	Graph graph, invertGraph;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	BuildGraph(inputFile, graph, invertGraph);

	std::cout << "Graph:" << std::endl;
	PrintGraph(graph);

	std::cout << "\nInvert Graph:" << std::endl;
	PrintGraph(invertGraph);

	std::cout << (SearchComponent(graph, invertGraph) == 1 ? "Yes" : "No") << std::endl;

	std::cout << SearchComponent(graph, invertGraph) << std::endl;

	return 0;
}


