#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <algorithm>

struct Vertex
{
	size_t numberVertex;
	size_t colorVertex = 0;
	std::vector<std::shared_ptr<Vertex>> vertexList;
};

typedef std::vector<std::shared_ptr<Vertex>> Graph;

bool IsExistsVertex(Graph const &graph, Vertex const &vertex)
{
	for (auto existsVertex : graph)
	{
		if (existsVertex->numberVertex == vertex.numberVertex)
			return true;
	}

	return false;
}

void BuildGraph(std::ifstream &inputFile, Graph &graph)
{
	std::string str;

	while (std::getline(inputFile, str))
	{
		std::stringstream stream(str);
		std::string vertexStr;
		Vertex startVertex;

		stream >> vertexStr;
		startVertex.numberVertex = stoul(vertexStr);

		while (stream.good())
		{
			Vertex endVertex;
			stream >> endVertex.numberVertex;

			if(!IsExistsVertex(graph, endVertex))
				startVertex.vertexList.push_back(std::make_shared<Vertex>(endVertex));
		}
		graph.push_back(std::make_shared<Vertex>(startVertex));
	}
}

void PrintGraph(const Graph &graph, size_t colorCount)
{
	std::cout << "Painted graph:" << std::endl;
	for (auto vertex : graph) 
	{
		std::cout << vertex->numberVertex << " - " << vertex->colorVertex << std::endl;
	}

	std::cout << "Count color:" << colorCount << std::endl;
}

Graph::iterator FindFirstNotPaintedVertex(Graph &graph, Graph::iterator ptrVertex)
{
	for (auto it = ptrVertex; it != end(graph); ++it) 
	{
		if (!(*it)->colorVertex) 
		{
			return it;
		}
	}

	return end(graph);
}

void ColorVertexSecondNeighborhood(std::shared_ptr<Vertex> &vertex, Graph::iterator &ptrVertex, size_t colorNumber)
{
	vertex->colorVertex = colorNumber;

	for (auto vertexFromList : vertex->vertexList)
	{
		if (!IsExistsVertex((*ptrVertex)->vertexList, *vertexFromList))
			((*ptrVertex)->vertexList).push_back(vertexFromList);
	}
}

void FindVertexSecondNeighborhood(std::shared_ptr<Vertex> vertex, size_t colorNumber, Graph::iterator &ptrVertex)
{
	bool isAdjacent = false;
	for (auto it = (*ptrVertex)->vertexList.begin(); it != (*ptrVertex)->vertexList.end(); ++it)
	{
		if (vertex->numberVertex == (*it)->numberVertex)
		{
			isAdjacent = true;
			break;
		}
	}

	if (!isAdjacent)
	{
		ColorVertexSecondNeighborhood(vertex, ptrVertex, colorNumber);
	}
}

void PaintVertexSecondNeighborhood(Graph &graph, size_t colorNumber, Graph::iterator ptrVertex)
{
	Graph::iterator it = FindFirstNotPaintedVertex(graph, ptrVertex);

	while (it != graph.end())
	{
		FindVertexSecondNeighborhood(*it, colorNumber, ptrVertex);
		it = FindFirstNotPaintedVertex(graph, ++it);
	}
}


void ColorGraph(Graph &graph, size_t &colorCount)
{
	size_t colorNumber = 0;
	Graph::iterator notPaintedVertex = FindFirstNotPaintedVertex(graph, graph.begin());
	
	while (notPaintedVertex != graph.end())
	{
		++colorNumber;
		(*notPaintedVertex)->colorVertex = colorNumber;
		PaintVertexSecondNeighborhood(graph, colorNumber, notPaintedVertex);
		notPaintedVertex = FindFirstNotPaintedVertex(graph, graph.begin());
	}

	colorCount = colorNumber;
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
	size_t colorCount = 0;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	BuildGraph(inputFile, graph);
	ColorGraph(graph, colorCount);
	PrintGraph(graph, colorCount);
	
	return 0;
}
