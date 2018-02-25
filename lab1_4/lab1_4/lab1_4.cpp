#include "stdafx.h"

int main()
{
	boost::timer t;
	const int k = 3;
	const int n = 100;
	std::vector<int> c(k + 1);

	for (int i = 1; i <= k; i++)
	{
		c[i] = i;
	}

	c[0] = -1;
	int j = 1;

	t.restart();

	while (j != 0)
	{
		j = k;

		while (c[j] == (n - k + j))
		{
			j--;
		}

		while (std::next_permutation(c.begin() + 1, c.end()));

		c[j]++;

		for (int i = j + 1; i <= k; i++)
		{
			c[i] = c[i - 1] + 1;
		}	
	}

	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}

