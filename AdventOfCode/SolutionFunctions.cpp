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
	inputfile.close();

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

void DayThreeSolution(std::string input)
{
	int Total = 0;
	std::string sinput = "";
	std::regex mulReg("mul\\(([0-9]+),([0-9]+)\\)");
	std::regex doDontReg(".*(do\\(\\)|don't\\(\\)).*");
	std::smatch match, doDontMatch;
	bool bDoAction = true;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file " << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		sinput += line;
	}
	inputfile.close();

	std::string::const_iterator csearch = sinput.cbegin();

	while (std::regex_search(csearch, sinput.cend(), match, mulReg))
	{
		std::string prefix = match.prefix();
		std::regex_match(prefix, doDontMatch, doDontReg);
		if (doDontMatch.size() > 0)
		{
			if (doDontMatch[doDontMatch.size() - 1] == "do()")
			{
				bDoAction = true;
			}
			else
			{
				bDoAction = false;
			}
		}
		if (bDoAction)
		{
			Total += std::stoi(match[1]) * std::stoi(match[2]);
		}
		csearch = match.suffix().first;
	}

	std::cout << "Total multiplications is " << Total << "\n";
}

void DayFourSolution(std::string input)
{
	int totalXmasCount = 0, totalMasCrossCount = 0;
	std::vector<std::vector<char>> grid;
	std::vector<std::pair<int, int>> charXPos;
	std::vector<std::pair<int, int>> charAPos;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file " << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		std::vector<char> lineVec;
		if (line.size() > 0)
		{
			for (int l = 0; l < line.size(); l++)
			{
				lineVec.push_back(line[l]);
				if (line[l] == 'X')
				{
					charXPos.push_back(std::pair<int, int>(l, grid.size()));
				}
				if (line[l] == 'A')
				{
					charAPos.push_back(std::pair<int, int>(l, grid.size()));
				}
			}
		}
		grid.push_back(lineVec);
	}
	inputfile.close();


	for (auto xLocation : charXPos)
	{
		totalXmasCount += GetXmasMatchesP1(grid, xLocation.first, xLocation.second);
	}

	std::cout << "Total number of 'XMAS' in grid is " << totalXmasCount << "\n";

	for (auto aLocation : charAPos)
	{
		if (GetXmasMatchesP2(grid, aLocation.first, aLocation.second)) 
		{ 
			totalMasCrossCount++; 
		}
	}
	std::cout << "Total number of Cross 'MAS' in grid is " << totalMasCrossCount << "\n";
}

int GetXmasMatchesP1(std::vector<std::vector<char>> grid, const int x, const int y)
{
	int matches = 0;
	if (grid.size() == 0) { return matches; }

	//Left
	if (x - 3 >= 0 &&
		grid[y][x-1] == 'M' && grid[y][x-2] == 'A' && grid[y][x-3] == 'S')
	{
		matches++;
	}
	//Right
	if (x + 3 < grid[0].size() &&
		grid[y][x+1] == 'M' && grid[y][x+2] == 'A' && grid[y][x+3] == 'S')
	{
		matches++;
	}

	//Up
	if (y - 3 >= 0 &&
		grid[y-1][x] == 'M' && grid[y-2][x] == 'A' && grid[y-3][x] == 'S')
	{
		matches++;
	}
	
	//Down
	if (y + 3 < grid.size() &&
		grid[y + 1][x] == 'M' && grid[y + 2][x] == 'A' && grid[y + 3][x] == 'S')
	{
		matches++;
	}

	//diag up-left
	if ((x - 3 >= 0 && y - 3 >= 0) &&
		grid[y - 1][x - 1] == 'M' && grid[y - 2][x - 2] == 'A' && grid[y - 3][x - 3] == 'S')
	{
		matches++;
	}

	//diag up-right
	if ((x + 3 < grid[0].size() && y - 3 >= 0) &&
		grid[y - 1][x + 1] == 'M' && grid[y - 2][x + 2] == 'A' && grid[y - 3][x + 3] == 'S')
	{
		matches++;
	}

	//diag down-left
	if ((x - 3 >= 0 && y + 3 < grid.size()) &&
		grid[y + 1][x - 1] == 'M' && grid[y + 2][x - 2] == 'A' && grid[y + 3][x - 3] == 'S')
	{
		matches++;
	}

	//diag down-right
	if ((x + 3 < grid[0].size() && y + 3 < grid.size()) &&
		grid[y + 1][x + 1] == 'M' && grid[y + 2][x + 2] == 'A' && grid[y + 3][x + 3] == 'S')
	{
		matches++;
	}

	return matches;
}

bool GetXmasMatchesP2(std::vector<std::vector<char>> grid, const int x, const int y)
{
	if (grid.size() == 0) { return false; }

	if (grid.size() == 0 || 
		(x - 1 < 0 || y - 1 < 0 || y + 1 >= grid.size() || x + 1 >= grid[0].size()) )
	{
		return false;
	}

	if ((grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S') ||
		grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M')
	{
		if ((grid[y - 1][x + 1] == 'M' && grid[y + 1][x - 1] == 'S') ||
			grid[y - 1][x + 1] == 'S' && grid[y + 1][x - 1] == 'M')
		{
			return true;
		}
	}

	return false;
}

void DayFiveSolution(std::string input)
{
	int combinedMidScore = 0, combinedFixedMidScore = 0;
	std::unordered_map<int, std::set<int>> Rules;
	std::vector<std::vector<int>> PageNumbers;
	std::vector<int> InvalidSequences;
	bool bRulesRead = false;
	std::ifstream inputfile(input);

	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		if (line == "")
		{
			bRulesRead = true;
		}
		else
		{
			if (!bRulesRead)
			{
				std::string::size_type dividedPos = line.find('|');
				int page1 = std::stoi(line.substr(0, dividedPos));
				int page2 = std::stoi(line.substr(dividedPos + 1, line.size()));
				Rules[page1].insert(page2);
			}
			else
			{
				std::vector<int> sequence;
				std::string number;
				std::stringstream ss(line);
				while (std::getline(ss, number, ','))
				{
					sequence.push_back(std::stoi(number));
				}
				PageNumbers.push_back(sequence);
			}
		}
	}
	inputfile.close();

	for (int i = 0; i < PageNumbers.size(); i++)
	{
		if (checkIfSequenceValid(PageNumbers[i], Rules))
		{
			combinedMidScore += PageNumbers[i][PageNumbers[i].size() / 2];
		}
		else
		{
			InvalidSequences.push_back(i);
		}
	}

	std::cout << "Total mid page numbers is " << combinedMidScore << "\n";

	for (int i = 0; i < InvalidSequences.size(); i++)
	{
		combinedFixedMidScore += FixInvalidSequence(PageNumbers[InvalidSequences[i]], Rules);
	}

	std::cout << "Total mid page numbers for fixed sets is " << combinedFixedMidScore << "\n";
}

bool checkIfSequenceValid(std::vector<int> sequence, std::unordered_map<int, std::set<int>> Rules)
{
	std::vector<int> seenNumbers;
	int throwaway;

	if (sequence.size() == 0) { return true; }
	seenNumbers.push_back(sequence[0]);

	for (int i = 1; i < sequence.size(); i++)
	{
		if (!checkNumbersValid(Rules[sequence[i]], seenNumbers, throwaway))
		{
			return false;
		}
		seenNumbers.push_back(sequence[i]);
	}

	return true;
}

int FixInvalidSequence(std::vector<int> &sequence, std::unordered_map<int, std::set<int>> Rules)
{
	int insertIndex;
	std::vector<int>::iterator iter;
	std::vector<int> seenNumbers;

	if (sequence.size() == 0) { return true; }
	seenNumbers.push_back(sequence[0]);

	for (int i = 1; i < sequence.size(); i++)
	{
		if (!checkNumbersValid(Rules[sequence[i]], seenNumbers, insertIndex))
		{
			int temp = sequence[i];
			sequence.erase(sequence.begin() + i);
			iter = sequence.begin() + insertIndex;
			sequence.insert(iter, temp);
			i = insertIndex;
			seenNumbers.resize(i);
			seenNumbers.push_back(sequence[insertIndex]);
		}
		else
		{
			seenNumbers.push_back(sequence[i]);
		}

	}

	return sequence[sequence.size()/2];
}

bool checkNumbersValid(std::set<int> InvalidNums, std::vector<int> NumsSeen, int &NumsSeenIndex)
{
	for (int i = 0; i < NumsSeen.size(); i++)
	{
		if (InvalidNums.find(NumsSeen[i]) != InvalidNums.end())
		{
			NumsSeenIndex = i;
			return false;
		}
	}

	return true;
}

void DaySixSolution(std::string input)
{
	std::vector<std::vector<char>> map;
	std::pair<int, int> playerPos;
	bool bFoundPlayer = false;
	int playerDir = direction::UP;
	int PositionsUsed = 0;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		std::vector<char> data(line.begin(), line.end());
		if (!bFoundPlayer)
		{
			std::size_t player = line.find_first_of("<>^");
			if (player != std::string::npos)
			{
				if (line[player] == '>')
				{
					playerDir = direction::RIGHT;
				}
				else if (line[player] == '<')
				{
					playerDir = direction::LEFT;
				}
				else if (line[player] == '^')
				{
					playerDir = direction::UP;
				}
				playerPos = std::pair<int, int>{ map.size(),player};
				bFoundPlayer = true;
			}
		}
		map.push_back(data);
	}

	if (map.size() < 0 || bFoundPlayer != true)
	{
		return;
	}

	while ( (playerPos.first >= 0 && playerPos.first < map.size()) &&
		    playerPos.second >= 0 && playerPos.second < map[0].size())
	{
		if (map[playerPos.first][playerPos.second] != 'X')
		{
			PositionsUsed++;
			map[playerPos.first][playerPos.second] = 'X';
		}

		switch (playerDir)
		{
		case UP:
			if (playerPos.first - 1 >= 0 &&
				map[playerPos.first - 1][playerPos.second] == '#')
			{
				playerDir++;
			}
			else
			{
				playerPos.first--;
			}
			break;
		case RIGHT:
			if (playerPos.second + 1 < map[0].size() && 
				map[playerPos.first][playerPos.second+1] == '#')
			{
				playerDir++;
			}
			else
			{
				playerPos.second++;
			}
			break;
		case DOWN:
			if (playerPos.first + 1 < map.size() &&
				map[playerPos.first + 1][playerPos.second] == '#')
			{
				playerDir++;
			}
			else
			{
				playerPos.first++;
			}
			break;
		case LEFT:
			if (playerPos.second-1 >= 0 && 
				map[playerPos.first][playerPos.second-1] == '#')
			{
				playerDir = direction::UP;
			}
			else
			{
				playerPos.second--;
			}
			break;
		default:
			break;
		}
	}

	std::cout << "Total distinct positions visited: " << PositionsUsed << "\n";
}