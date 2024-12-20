#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

std::vector<int> QuickSortInt(std::vector<int> nums);
bool isAscendingOrder(std::vector<int> Sequence);

bool IsOutOfBounds(std::pair<int,int> location, std::pair<int, int> maxSize);