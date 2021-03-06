#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include "sstream"

typedef std::vector<std::vector<size_t>> Graph;


void BuildGraph(std::ifstream &inputFile, Graph &graph, size_t &countRightVertex)
{
	std::string str, vertexStr;
	size_t left, right, startVertex = 0, endVertex = 0;
	inputFile >> left >> right;

	graph.resize(left);

	while (std::getline(inputFile, str))
	{
		std::stringstream stream(str);

		stream >> startVertex;
		--startVertex;

		while (stream.good())
		{
			stream >> endVertex;
			--endVertex;
			graph[startVertex].push_back(endVertex);
		}
	}

	countRightVertex = right;
}

bool FindMaxMatch(std::vector<bool> &used, std::vector<size_t> &pair,const Graph &graph, size_t in, bool &isFind)
{
	if (used[in]) 
		return false;

	used[in] = true;

	for (size_t i = 0; i < graph[in].size(); ++i) 
	{
		size_t to = graph[in][i];

		if ((pair[to] == -1) || (FindMaxMatch(used, pair, graph, pair[to], isFind)))
		{
			pair[to] = in;
			isFind = true;
			return true;
		}
	}
	return false;
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
	size_t countRightVertex;
	std::vector<size_t> pair;
	std::vector<bool> used;
	bool isFind = false;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	BuildGraph(inputFile, graph, countRightVertex);
	pair.assign(countRightVertex, -1);

	for (size_t in = 0; in < graph.size(); ++in)
	{
		used.assign(graph.size(), false);
		FindMaxMatch(used, pair, graph, in, isFind);
	}

	if (!isFind)
	{
		std::cout << "No" << std::endl;
	}
	else
	{
		std::cout << "Yes" << std::endl;

		for (size_t i = 0; i < pair.size(); ++i)
		{
			if (pair[i] != -1)
				std::cout << pair[i] + 1 << " " << i + 1 << std::endl;
		}
	}
}