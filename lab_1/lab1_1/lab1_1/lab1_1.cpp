#include "stdafx.h"

int main()
{
	boost::timer t;
	const size_t n = 10;
	std::array<size_t, n + 2> Pi;
	std::array<size_t, n + 2> p;
	std::array<size_t, n + 2> d;

	for (size_t i = 1; i <= n; ++i)
	{
		Pi[i] = i;
		p[i] = i;
		d[i] = -1;
	}

	d[1] = 0;
	size_t m = n + 1;

	Pi[0] = Pi[m] = m;

	t.restart();

	while (m != 1)
	{
		m = n;

		while (Pi[p[m] + d[m]] > m)
		{
			d[m] = (-1) * d[m];
			--m;
		}

		std::swap(Pi[p[m]], Pi[p[m] + d[m]]);
		std::swap(p[Pi[p[m]]], p[m]);
	}

	double duration = t.elapsed();
	std::cout << duration << std::endl;
	return 0;
}

