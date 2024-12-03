#include "Utility.h"

std::vector<int> QuickSortInt(std::vector<int> nums)
{
	if (nums.size() <= 1) { return nums; }

	int pivot = rand() % (nums.size() - 1);
	int PivotCount = 1;

	std::vector<int> Less, More, Final;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == nums[pivot] && i != pivot)
		{
			//Avoid using the same Pivot again
			PivotCount++;
		}
		if (nums[i] < nums[pivot])
		{
			Less.push_back(nums[i]);
		}
		else if (nums[i] > nums[pivot])
		{
			More.push_back(nums[i]);
		}
	}

	Final = QuickSortInt(Less);
	for (int i = 0; i < PivotCount; i++)
	{
		Final.push_back(nums[pivot]);
	}
	std::vector<int> RightSort = QuickSortInt(More);
	Final.insert(Final.end(), RightSort.begin(), RightSort.end());

	return Final;
}
