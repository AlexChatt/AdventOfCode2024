#include "SolutionFunctions.h"

int DayOneSolution(std::string input)
{
	int diffSum = 0;
	int similarityScore = 0;
	std::vector<int> List1, List2;
	std::unordered_map<int, int> Instances;

	std::ifstream inputfile(input);

	if (!inputfile)
	{
		std::cout << "Can not open input file";
		return 1;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		if (line.size() > 0)
		{
			List1.push_back(std::stoi(line.substr(0, line.find(' '))));
			List2.push_back(std::stoi(line.substr(line.find(' ') + 1)));
		}
	}
	inputfile.close();

	srand(time(NULL));
	List1 = QuickSortInt(List1);
	List2 = QuickSortInt(List2);

	for (int i = 0; i < List1.size() && i < List2.size(); i++)
	{
		diffSum += std::abs(List1[i] - List2[i]);
	}

	std::cout << "The total distance between the lists is " << diffSum << "\n";

	for (int i = 0; i < List2.size(); i++)
	{
		Instances[List2[i]]++;
	}

	for (int i = 0; i < List1.size(); i++)
	{
		if (Instances.find(List1[i]) != Instances.end())
		{
			similarityScore += List1[i] * Instances[List1[i]];
		}
	}

	std::cout << "The total similarity score for the lists is " << similarityScore << "\n";
}
