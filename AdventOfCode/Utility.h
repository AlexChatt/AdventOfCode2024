#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

std::vector<int> QuickSortInt(std::vector<int> nums);
bool isAscendingOrder(std::vector<int> Sequence);

bool IsOutOfBounds(std::pair<int,int> location, std::pair<int, int> maxSize);

template <typename T>
void PrintMap(const std::vector<std::vector<T>>& Map, bool bSpaces)
{
	for (int i = 0; i < Map.size(); i++)
	{
		for (int j = 0; j < Map[i].size(); j++)
		{
			std::cout << Map[i][j];
			if (bSpaces)
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

