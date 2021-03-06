#include "stdafx.h"

const unsigned matrixSize = 4;
typedef std::array<std::array<size_t, matrixSize>, matrixSize> Matrix;

bool ReadMatrix(std::istream& inputFile, Matrix& matrix)
{
	for (int i = 0; i < matrixSize; ++i)
	{
		for (int j = 0; j < matrixSize; ++j)
		{
			if (!(inputFile >> matrix[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

size_t findLengthPath(const std::array<size_t, matrixSize> &path, Matrix &matrix)
{
	size_t currentLengthPath = 0;

	for (size_t i = 0; i < path.size(); ++i)
	{
		size_t j = (i + 1) % path.size();

		if (matrix[path[i]][path[j]] != 0)
		{
			currentLengthPath += matrix[path[i]][path[j]];
		}
		else
		{
			currentLengthPath = SIZE_MAX;
			break;
		}
	}

	return currentLengthPath;
}

bool SearchHamiltonCycleMinLength(Matrix& matrix, std::array<size_t, matrixSize> &minPath, size_t &minLengthPath)
{
	std::array<size_t, matrixSize> currentPath;
	size_t currentLength = 0;
	bool find = false;

	for (size_t i = 0; i < matrixSize; ++i)
	{
		currentPath[i] = i;
	}

	do
	{
		currentLength = findLengthPath(currentPath, matrix);

		if (currentLength < minLengthPath)
		{
			minLengthPath = currentLength;
			minPath = currentPath;
			find = true;
		}
	}
	while (std::next_permutation(currentPath.begin(), currentPath.end()));

	return find;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid argument count\n"
			<< "usage: gamilton.exe <inputMatrixFile>" << std::endl;
		return 1;
	}

	Matrix inputMatrix;
	std::ifstream inputFile;
	inputFile.open(argv[1]);

	if (!inputFile)
	{
		std::cout << "File not found" << std::endl;
		return 1;
	}

	if (!ReadMatrix(inputFile, inputMatrix))
	{
		std::cout << "Could not read data from file" << std::endl;
		return 1;
	}

	std::array<size_t, matrixSize> minPath;
	size_t minLengthPath = SIZE_MAX;

	if (SearchHamiltonCycleMinLength(inputMatrix, minPath, minLengthPath))
	{
		std::transform(minPath.begin(), minPath.end(), minPath.begin(), [=](size_t top) {return top += 1; });

		std::cout << "Hamilton Cycle: " << std::endl;
		std::copy(minPath.begin(), minPath.end(), std::ostream_iterator<size_t>(std::cout, " "));

		std::cout << "min length: " << minLengthPath << std::endl;
	}
	else
	{
		std::cout << "Cycle not found" << std::endl;
	}

	return 0;
}

