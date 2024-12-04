#include "SolutionFunctions.h"

void DayOneSolution(std::string input)
{
	int diffSum = 0;
	int similarityScore = 0;
	std::vector<int> List1, List2;
	std::unordered_map<int, int> Instances;

	std::ifstream inputfile(input);

	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
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

void DayTwoSolution(std::string input)
{
	std::vector<std::vector<int>> sequences;
	int ValidSequences = 0;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file " << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		std::vector<int> s;
		if (line.size() > 0)
		{
			std::string snumber;
			std::stringstream ss(line);
			while (std::getline(ss, snumber, ' '))
			{
				s.push_back(std::stoi(snumber));
			}
		}
		sequences.push_back(s);
	}

	// can do this with divide and conqure but ill be lazy and use brute force since
	// the size of the sequences are small
	for (auto& sequence : sequences)
	{
		int badIndex;
		bool bisAscending = isAscendingOrder(sequence);
		if (CheckValidSequence(sequence, badIndex, bisAscending, -1))
		{
			ValidSequences++;
		}
		else
		{
			int preplus = badIndex+1;
			if(CheckValidSequence(sequence, badIndex, bisAscending, badIndex) ||
				CheckValidSequence(sequence, badIndex, bisAscending, preplus))
			{
				ValidSequences++;
			}
		}
	}

	std::cout << "The Number of Valid Sequences are " << ValidSequences << "\n";
}
bool CheckValidSequence(std::vector<int> Sequence, int& problemIndex, bool bisAscending, int ignoreElement)
{
	bool bValidSequence = true;
	int previousI = 0;

	if (ignoreElement == 0)
	{
		previousI++;
	}

	for (int x = previousI + 1; x < Sequence.size(); x++)
	{
		if (ignoreElement == x)
		{
			continue;
		}

		if ((bisAscending && Sequence[x] <= Sequence[previousI]) ||
			(!bisAscending && Sequence[x] >= Sequence[previousI]))
		{
			problemIndex = previousI;
			return false;
		}

		if (abs(Sequence[previousI] - Sequence[x]) > 3)
		{
			problemIndex = previousI;
			return false;
		}

		previousI = x;
	}

	return true;
}