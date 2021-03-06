#include "stdafx.h"

struct Object
{
	int number = 0;
	int weight = 0;
	int price = 0;
};

void SetListOfObjects(std::vector<Object> &listObjects, std::istream& file)
{
	std::string Str;
	Object currentObject;

	currentObject.number = 0;

	while (!file.eof())
	{
    	currentObject.number++;
		file >> currentObject.weight;
		file >> currentObject.price;
		listObjects.push_back(currentObject);
	}
}

Object putObjectInBackpack(std::vector<Object> listObjects, std::vector<int> currentSetOfObjects)
{
	Object backpack;
	backpack.price = 0;
	backpack.weight = 0;

	for (int i = 1; i < (int)currentSetOfObjects.size(); i++)
	{
	    backpack.price = backpack.price + listObjects[currentSetOfObjects[i] - 1].price;
	    backpack.weight = backpack.weight + listObjects[currentSetOfObjects[i] - 1].weight;
	}

	return backpack;
}

void FillBackpack(std::vector<Object> listObjects, const int maxWeight)
{
    int k = 1;
	const int n = listObjects.size();
	int maxPrice = 0;
	std::vector<int> сurrentSetOfObjects;
	Object weightBackpack;

	while (k <= n)
	{
		std::vector<int> c(k + 1);

		for (int i = 1; i <= k; ++i)
		{
			c[i] = i;
		}

		c[0] = -1;
		int j = 1;

		while (j != 0)
		{
			weightBackpack = putObjectInBackpack(listObjects, c);
			if ((weightBackpack.weight <= maxWeight) && (weightBackpack.price > maxPrice))
			{
				сurrentSetOfObjects = c;
				maxPrice = weightBackpack.price;
			}

			j = k;

			while (c[j] == (n - k + j))
			{
				j--;
			}

			c[j]++;

			for (int i = j + 1; i <= k; i++)
			{
				c[i] = c[i - 1] + 1;
			}
		}

		k++;
	}

	std::cout << "Set in a backpack:\n";
	std::copy(сurrentSetOfObjects.begin() + 1, сurrentSetOfObjects.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	const int maxWeight = 100;
	std::vector<Object> listObjects;
	std::ifstream inputFile;

	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: lab1_6.exe <inputFile>\n";
		return 1;
	}

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found\n";
		return 1;
	}

	SetListOfObjects(listObjects, inputFile);
	FillBackpack(listObjects, maxWeight);

	return 0;
}

