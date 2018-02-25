#include "stdafx.h"

int main()
{
	boost::timer t;
	const int n = 10;
	int Pi[n + 2];
	int p[n + 2];
	int d[n + 2];

	for (int i = 1; i <= n; i++)
	{
		Pi[i] = i;
		p[i] = i;
		d[i] = -1;
	}

	d[1] = 0;
	int m = n + 1;

	Pi[0] = Pi[m] = m;

	t.restart();

	while (m != 1)
	{
		m = n;

		while (Pi[p[m] + d[m]] > m)
		{
			d[m] = (-1) * d[m];
			m --;
		}

		std::swap(Pi[p[m]], Pi[p[m] + d[m]]);
		std::swap(p[Pi[p[m]]], p[m]);
	}

	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}

