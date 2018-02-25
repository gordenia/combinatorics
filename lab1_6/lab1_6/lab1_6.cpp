#include "stdafx.h"

struct Object
{
	int number = 0;
	int weight = 0;
	int price = 0;
};

void setListOfObjects(std::vector<Object> &listObjects)
{
	std::ifstream file("F1.txt");
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

	for (int i = 1; i < currentSetOfObjects.size(); i++)
	{
	    backpack.price = backpack.price + listObjects[currentSetOfObjects[i] - 1].price;
	    backpack.weight = backpack.weight + listObjects[currentSetOfObjects[i] - 1].weight;
	}

	return backpack;
}

void fillBackpack(std::vector<Object> listObjects, const int maxWeight)
{
    int k = 1;
	const int n = listObjects.size();
	int maxPrice = 0;
	std::vector<int> surrentSetOfObjects;
	Object weightBackpack;

	while (k <= n)
	{
		std::vector<int> c(k + 1);

		for (int i = 1; i <= k; i++)
		{
			c[i] = i;
		}

		c[0] = -1;
		int j = 1;

		while (j != 0)
		{
			weightBackpack = putObjectInBackpack(listObjects, c);
			if ((weightBackpack.weight < maxWeight) && (weightBackpack.price > maxPrice))
			{
				surrentSetOfObjects = c;
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
	std::copy(surrentSetOfObjects.begin() + 1, surrentSetOfObjects.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "\n";
}

int main()
{
	int maxWeight = 10;
	std::vector<Object> listObjects;

	setListOfObjects(listObjects);
	fillBackpack(listObjects, maxWeight);

	return 0;
}

