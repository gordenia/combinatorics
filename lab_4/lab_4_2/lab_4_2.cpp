#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Vertex
{
	int overflow = 0;
	int h = 0;
};

struct Edge
{
	int vertex1, vertex2;
	int capacity, flow = 0;
};

typedef std::vector<Edge> Graph;
typedef std::vector<Vertex> VertexList;

void FillVertexList(Graph &graph, std::vector<Vertex> &vertexList, int countVertex)
{
	Vertex vertex;

	for (int i = 0; i < countVertex; ++i)
	{
		vertexList.push_back(vertex);
	}
}

void BuildGraph(std::ifstream &inputFile, Graph &graph, std::vector<Vertex> &vertexList, int &countVertex)
{
	std::string str;
	Edge newEdge;

	std::getline(inputFile, str);
	std::stringstream number(str);

	number >> countVertex;

	while (std::getline(inputFile, str))
	{
		std::stringstream stream(str);
		stream >> newEdge.vertex1 >> newEdge.vertex2 >> newEdge.capacity;
		graph.push_back(newEdge);
	}

	FillVertexList(graph, vertexList, countVertex);
}

void RunFlow(std::vector<Edge> &graph, std::vector<Vertex> &vertexList)
{
	vertexList[graph[0].vertex1].h = vertexList.size();

	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[i].vertex1 == graph[0].vertex1)
		{
			graph[i].flow = graph[i].capacity;
			vertexList[graph[i].vertex2].overflow += graph[i].flow;

			Edge newEdge;
			newEdge.vertex1 = graph[i].vertex2;
			newEdge.vertex2 = 0;
			newEdge.capacity = 0;
			newEdge.flow = -graph[i].flow;
			graph.push_back(newEdge);
		}
	}
}

int FoundOverflowVertex(std::vector<Vertex> &vertexList)
{
	for (int i = 1; i < vertexList.size()-1; ++i)
		if (vertexList[i].overflow > 0)
			return i;

	return -1;
}

void AddNewEdge(int i, int flow, std::vector<Edge> &graph)
{
	int vertex1 = graph[i].vertex2;
	int vertex2 = graph[i].vertex1;

	for (int j = 0; j < graph.size(); j++)
	{
		if (graph[j].vertex2 == vertex2 && graph[j].vertex1 == vertex1)
		{
			graph[j].flow -= flow;
			return;
		}
	}

	Edge newEdge;

	newEdge.vertex1 = vertex1;
	newEdge.vertex2 = vertex2;
	newEdge.capacity = flow;

	graph.push_back(newEdge);
}

bool Push(int vertex, std::vector<Edge> &graph, std::vector<Vertex> &vertexList)
{
	for (int i = 0; i < graph.size(); ++i)
	{
		if (graph[i].vertex1 == vertex)
		{
			if (graph[i].flow == graph[i].capacity)
				continue;

			if (vertexList[vertex].h > vertexList[graph[i].vertex2].h)
			{
				int flow = std::min(graph[i].capacity - graph[i].flow, vertexList[vertex].overflow);

				vertexList[vertex].overflow -= flow;
				vertexList[graph[i].vertex2].overflow += flow;
				graph[i].flow += flow;

				AddNewEdge(i, flow, graph);

				return true;
			}
		}
	}

	return false;
}

void Relabel(int vertex, std::vector<Edge> &graph, std::vector<Vertex> &vertexList)
{
	int minimumHeight = INT_MAX;
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[i].vertex1 == vertex)
		{
			if (graph[i].flow == graph[i].capacity)
				continue;

			if (vertexList[graph[i].vertex2].h < minimumHeight)
			{
				minimumHeight = vertexList[graph[i].vertex2].h;
				vertexList[vertex].h = minimumHeight + 1;
			}
		}
	}
}

void FindMaxFlow(std::vector<Edge> &graph, std::vector<Vertex> &vertexList)
{
	int foundVertex;
	RunFlow(graph, vertexList);
	foundVertex = FoundOverflowVertex(vertexList);

	while ((foundVertex != -1))
	{
		if (!Push(foundVertex, graph, vertexList))
			Relabel(foundVertex, graph, vertexList);

		foundVertex = FoundOverflowVertex(vertexList);
	}
}

void PrintGraph(std::vector<Edge> &graph, std::vector<Vertex> &vertexList)
{
	for (auto edge : graph) {
		if (edge.flow > 0)
		{
			std::cout << edge.vertex1 << " -> " << edge.vertex2 << ": " 
				<< edge.flow << std::endl;
		}
	};
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
	VertexList vertexList;
	int countVertex = 0;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	BuildGraph(inputFile, graph, vertexList, countVertex);
	FindMaxFlow(graph, vertexList);
	PrintGraph(graph, vertexList);

	std::cout << "MaxFlow: " << vertexList.back().overflow << std::endl;
    return 0;
}

