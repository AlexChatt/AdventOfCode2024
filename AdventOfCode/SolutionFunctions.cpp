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
	std::vector<std::pair<int, int>> visitedLocation;
	int loopPlacements = 0;

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
	inputfile.close();

	if (map.size() < 0 || bFoundPlayer != true)
	{
		return;
	}

	RouteTraverse(map, playerPos, playerDir, visitedLocation);
	std::cout << "Total distinct positions visited: " << visitedLocation.size() << "\n";

	/* Only place Barrel in locations we have walked */
	std::vector<std::pair<int, int>> throwaway;
	for (auto position : visitedLocation)
	{
		map[position.first][position.second] = '#';
		if (!RouteTraverse(map, playerPos, playerDir, throwaway))
		{
			loopPlacements++;
		}
		map[position.first][position.second] = '.';
	}

	std::cout << "Total different positions for looping guard: " << loopPlacements << "\n";
}

bool RouteTraverse(std::vector<std::vector<char>> map, std::pair<int, int> playerPos, int playerDir, std::vector<std::pair<int, int>>& visitedLocation)
{
	std::set<visitedPoints> PointsVisited;
	bool bPlayerMoved = true;

	while ((playerPos.first >= 0 && playerPos.first < map.size()) &&
		playerPos.second >= 0 && playerPos.second < map[0].size())
	{
		PointsVisited.insert(visitedPoints(playerPos.first, playerPos.second, playerDir));

		if (map[playerPos.first][playerPos.second] != 'X')
		{
			visitedLocation.push_back({playerPos.first, playerPos.second});
			map[playerPos.first][playerPos.second] = 'X';
		}

		bPlayerMoved = false;

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
				bPlayerMoved = true;
			}
			break;
		case RIGHT:
			if (playerPos.second + 1 < map[0].size() &&
				map[playerPos.first][playerPos.second + 1] == '#')
			{
				playerDir++;
			}
			else
			{
				playerPos.second++;
				bPlayerMoved = true;
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
				bPlayerMoved = true;
			}
			break;
		case LEFT:
			if (playerPos.second - 1 >= 0 &&
				map[playerPos.first][playerPos.second - 1] == '#')
			{
				playerDir = direction::UP;
			}
			else
			{
				playerPos.second--;
				bPlayerMoved = true;
			}
			break;
		default:
			break;
		}

		visitedPoints OldPoint(playerPos.first, playerPos.second, playerDir);
		if (PointsVisited.find(OldPoint) != PointsVisited.end() && bPlayerMoved)
		{
			/* We have been here before, we are loooooooping */
			return false;
		}
	}

	return true;
}

void DaySevenSolution(std::string input)
{
	long long int P1Answer = 0;
	std::vector<std::pair<long long int, std::vector<int>>> TotalWithNumbers;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		std::pair<long long int, std::vector<int>> temp;
		std::string snumber;
		std::stringstream ss(line);
		while (std::getline(ss, snumber, ' '))
		{
			if (snumber[snumber.size()-1] == ':')
			{
				snumber.pop_back();
				temp.first = std::stoll(snumber);
			}
			else
			{
				temp.second.push_back(std::stoll(snumber));
			}
		}
		TotalWithNumbers.push_back(temp);
	}
	inputfile.close();

	for (auto set : TotalWithNumbers)
	{
		if (RecursiveSolve(set.first, set.second, 1, set.second[0]))
		{
			P1Answer += set.first;
		}
	}
	std::cout << "Total calibration result is: " << P1Answer << "\n";
}

bool RecursiveSolve(long long int TargetNum, std::vector<int> numbers, int index, long long int sumSoFar)
{
	bool TargetFound = false;
	if (sumSoFar > TargetNum) { return false; }
	if (index == numbers.size())
	{
		if (sumSoFar == TargetNum)
		{
			return true;
		}
		return false;
	}

	TargetFound |= RecursiveSolve(TargetNum, numbers, index + 1, sumSoFar + numbers[index]);
	TargetFound |= RecursiveSolve(TargetNum, numbers, index + 1, sumSoFar * numbers[index]);
	std::string combined = std::to_string(sumSoFar);
	combined += std::to_string(numbers[index]);
	TargetFound |= RecursiveSolve(TargetNum, numbers, index + 1, std::stoll(combined));

	return TargetFound;
}

void DayEightSolution(std::string input)
{
	std::vector<std::vector<bool>> map;
	std::unordered_map<char, std::vector<antenna>> antennas;
	int antinode = 0;
	std::ifstream inputfile(input);

	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	int yLine = 0;
	while (std::getline(inputfile, line))
	{
		map.push_back(std::vector<bool>(line.size()));
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != '.')
			{
				antenna temp;
				temp.position = std::pair<int, int>{ i,yLine};
				antennas[line[i]].push_back(temp);
			}
		}
		yLine++;
	}
	inputfile.close();

	for (std::unordered_map<char, std::vector<antenna>>::iterator it = antennas.begin(); it != antennas.end(); ++it)
	{
		antinode += GetAntennaPoints(it->second, map);
	}

	std::cout << "Unique locations in the map that contain antinodes are: " << antinode << "\n";
}

int GetAntennaPoints(std::vector<antenna> antentas, std::vector<std::vector<bool>>& map)
{
	int newAntinode = 0;
	std::pair<int, int> mapsize;

	if (map.size() <= 0) { return 0; }

	mapsize = { map[0].size(), map.size() };

	for (int i = 0; i < antentas.size(); i++)
	{
		for (int j = i+1; j < antentas.size(); j++)
		{
			std::pair<int, int> p1 = antentas[i].position, p2 = antentas[j].position;
			std::pair<int, int> increaseP1, increaseP2;

			increaseP1 = { antentas[i].position.first - antentas[j].position.first, antentas[i].position.second - antentas[j].position.second };
			p1 = { increaseP1.first + p1.first, increaseP1.second + p1.second };
			while (!IsOutOfBounds(p1, mapsize))
			{
				if (!map[p1.first][p1.second])
				{
					newAntinode++;
					map[p1.first][p1.second] = true;
				}
				p1 = { increaseP1.first + p1.first, increaseP1.second + p1.second };
			}

			increaseP2 = { antentas[j].position.first - antentas[i].position.first, antentas[j].position.second - antentas[i].position.second };
			p2 = { increaseP2.first + p2.first, increaseP2.second + p2.second };
			while (!IsOutOfBounds(p2, mapsize))
			{
				if (!map[p2.first][p2.second])
				{
					newAntinode++;
					map[p2.first][p2.second] = true;
				}
				p2 = { increaseP2.first + p2.first, increaseP2.second + p2.second };
			}
		}
	}

	for (int i = 0; i < antentas.size() && antentas.size() > 1; i++)
	{
		if(!map[antentas[i].position.first][antentas[i].position.second])
		{
			map[antentas[i].position.first][antentas[i].position.second] = true;
			newAntinode++;
		}
	}

	return newAntinode;
}

void DayNineSolution(std::string input)
{
	std::vector<int> file;
	bool bisSpaces = false;
	long long int id = 0;
	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	std::getline(inputfile, line);
	for ( auto number : line )
	{
		int convert = number - '0';
		if (bisSpaces)
		{
			std::vector<int> tofill(convert, -1);
			file.insert(file.end(), tofill.begin(), tofill.end());
		}
		else
		{
			std::vector<int> tofill(convert, id);
			file.insert(file.end(), tofill.begin(), tofill.end());
			id++;
		}

		bisSpaces = !bisSpaces;
	}
	inputfile.close();


	DayNineP1(file);
	DayNineP2(file);
}

void DayNineP1(std::vector<int> file)
{
	//Sliding windows solution
	int min = 0, max = file.size() - 1;
	unsigned long long int checksum = 0, id = 0;

	while (file[max] == '.')
	{
		max--;
	}

	while (min <= max)
	{
		if (file[max] == -1)
		{
			max--;
		}
		else
		{
			if (file[min] == -1)
			{
				file[min] = file[max];
				file[max] = -1;
				max--;
			}
			min++;
		}
	}

	file.resize(max + 1);

	for (auto const number : file)
	{
		checksum += (int(number) * id);
		id++;
	}

	std::cout << "Resulting filesystem checksum of input is " << checksum << "\n";

}

void DayNineP2(std::vector<int> file)
{
	unsigned long long int checksum = 0, id = 0;
	std::map<int, std::pair<int, int>> fileMap;

	int CurrentNum = -1, count = 0, startingI = 0;
	for (int i = 0; i <= file.size(); i++)
	{
		if (i >= file.size() || file[i] != CurrentNum)
		{
			if (CurrentNum != -1)
			{
				fileMap[CurrentNum] = std::pair<int, int>{ startingI,count };
			}
			if(i < file.size()) { CurrentNum = file[i]; }
			count = 1;
			startingI = i;
		}
		else
		{
			count++;
		}
	}

	count = 0;
	while (fileMap.size() > 0)
	{
		auto mapit = (--fileMap.end());

		for (int i = 0; i < mapit->second.first; i++)
		{
			if (file[i] == -1)
			{
				count++;

				if (count == mapit->second.second)
				{
					int j, k;
					for (j = (i+1) - count, k = mapit->second.first; j < (i+1) && k < mapit->second.first + count; j++, k++)
					{
						file[j] = mapit->first;
						file[k] = -1;
					}
					break;
				}
			}
			else
			{
				count = 0;
			}
		}
		fileMap.erase(mapit->first);
	}

	// We go back to front looking through the file and can only attempt to 
	// move each file once, if we cant move it then we dont try again

	for (auto const number : file)
	{
		if (number != -1)
		{
			checksum += (int(number) * id);
		}
		id++;
	}

	std::cout << "Resulting filesystem checksum of input is " << checksum << "\n";

}

void DayTenSolution(std::string input)
{
	std::vector<std::vector<int>> Map;
	std::vector<std::pair<int, int>> StartingPoints;
	int trailHead = 0;
	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		std::vector<int> s;
		for (int i = 0; i < line.size(); i++)
		{
			int convert;
			if (line[i] == '.')
			{
				convert = -1;
			}
			else
			{
				convert = line[i] - '0';
			}
			s.push_back(convert);
			if (convert == 0)
			{
				StartingPoints.push_back(std::pair<int,int>(Map.size(),i));
			}
		}
		Map.push_back(s);
	}
	inputfile.close();

	for (int i = 0; i < StartingPoints.size(); i++)
	{
		std::set<std::pair<int, int>> NineSeen;
		trailHead += GetTrailHeads(StartingPoints[i], Map, NineSeen, false);
	}

	std::cout << "Sum of the scores of all trailheads on the topographic map is: " << trailHead << "\n";

	trailHead = 0;
	for (int i = 0; i < StartingPoints.size(); i++)
	{
		std::set<std::pair<int, int>> NineSeen;
		trailHead += GetTrailHeads(StartingPoints[i], Map, NineSeen, true);
	}
	std::cout << "The total sum of the ratings of all trailheads is: " << trailHead << "\n";
}

int GetTrailHeads(std::pair<int, int> location, std::vector<std::vector<int>> Map, std::set<std::pair<int,int>>& NineSeen, bool bP2)
{
	int trailHead = 0;

	if (Map[location.first][location.second] == 9)
	{
		if ((NineSeen.find(location) == NineSeen.end() && !bP2) || bP2)
		{
			NineSeen.insert(std::pair<int, int>{location.first, location.second});
			return 1;
		}
	}

	std::vector<std::pair<int, int>> NextSteps = getValidIncrease(location, Map);

	for (int i = 0; i < NextSteps.size(); i++)
	{
		trailHead += GetTrailHeads(NextSteps[i], Map, NineSeen, bP2);
	}

	return trailHead;
}

std::vector<std::pair<int, int>> getValidIncrease(std::pair<int, int> location, std::vector<std::vector<int>> Map)
{
	std::vector<std::pair<int, int>> NextSteps;

	if (Map.size() == 0) { return NextSteps; }

	int WantedNum = Map[location.first][location.second] + 1;

	if (!IsOutOfBounds({ location.first - 1, location.second }, { Map[0].size(), Map.size() }) &&
		Map[location.first -1][location.second] == WantedNum)
	{
		NextSteps.push_back({ location.first - 1, location.second });
	}
	if (!IsOutOfBounds({ location.first + 1, location.second }, { Map[0].size(), Map.size() }) &&
		Map[location.first + 1][location.second] == WantedNum)
	{
		NextSteps.push_back({ location.first + 1, location.second });
	}
	if (!IsOutOfBounds({ location.first, location.second - 1 }, { Map[0].size(), Map.size() }) &&
		Map[location.first][location.second -1] == WantedNum)
	{
		NextSteps.push_back({ location.first, location.second - 1});
	}	
	if (!IsOutOfBounds({ location.first, location.second + 1 }, { Map[0].size(), Map.size() }) &&
		Map[location.first][location.second +1] == WantedNum)
	{
		NextSteps.push_back({ location.first, location.second + 1});
	}

	return NextSteps;
}

void DayElevanSolution(std::string input)
{
	std::vector<long long> Stones;
	std::unordered_map<long long, long long> StonesMap;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	std::getline(inputfile, line);

	std::string snumber;
	std::stringstream ss(line);
	while (std::getline(ss, snumber, ' '))
	{
		long long number = std::stoi(snumber);
		Stones.push_back(number);
		StonesMap[number]++;
	}

	inputfile.close();

	// Part 1
	for (int i = 1; i <= 25; i++)
	{
		SimulateBlink(Stones);
	}

	for (int i = 1; i <= 75; i++)
	{
		SimulateBlink(StonesMap);
	}

	long long p2Stones = 0;
	for (auto stone : StonesMap)
	{
		p2Stones += stone.second;
	}

	std::cout << "The total number of stones after 25 blinks: " << Stones.size() << "\n";
	std::cout << "The total number of stones after 75 blinks: " << p2Stones << "\n";
}

void SimulateBlink(std::vector<long long> &stones)
{
	std::vector<long long> NewStones;

	for (int i = 0; i < stones.size(); i++)
	{
		if (stones[i] == 0)
		{
			NewStones.push_back(1);
		}
		else
		{
			std::string numToString = std::to_string(stones[i]);
			if (numToString.size() % 2 == 0)
			{
				long long latter = std::pow(10,numToString.size() / 2);
				NewStones.push_back(stones[i] / latter);
				NewStones.push_back(stones[i] % latter);
			}
			else
			{
				NewStones.push_back(stones[i] * 2024);
			}
		}
	}

	stones = NewStones;
}

void SimulateBlink(std::unordered_map<long long, long long>& stones)
{
	long long stoneCount = 0;

    // Take a copy to run with
	std::unordered_map<long long, long long> snapshotStones = stones;

	for (auto &key : snapshotStones)
	{
		if (key.second == 0) { continue; }

		stoneCount = key.second;
		stones[key.first] -= stoneCount;

		if (key.first == 0)
		{
			addToMap(stones, 1, stoneCount);
		}
		else
		{
			std::string numToString = std::to_string(key.first);
			if (numToString.size() % 2 == 0)
			{
				long long latter = std::pow(10, numToString.size() / 2);
				addToMap(stones, (key.first / latter), stoneCount);
				addToMap(stones, (key.first % latter), stoneCount);
			}
			else
			{
				addToMap(stones, key.first * 2024, stoneCount);
			}
		}
	}
}

void addToMap(std::unordered_map<long long, long long>& stones, long long stoneNum, long long stoneCount)
{
	if (stones.find(stoneNum) == stones.end())
	{
		stones[stoneNum] = 0;
	}
	stones[stoneNum] += stoneCount;
}

void DayTwelveSolution(std::string input)
{
	std::vector<std::vector<node>> garden;
	std::vector<std::vector<node>> regions;
	int TotalPrice = 0;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file " << input << "\n";
		return;
	}

	node newNode('y', std::pair<int, int>(1, 1));

	std::string line;
	int y = 0;
	while (std::getline(inputfile, line))
	{
		if (line.size() > 0)
		{
			std::vector<node> gardenLine;
			for (int x = 0; x < line.size(); x++)
			{
				node newNode(line[x], std::pair<int, int>(y, x));
				gardenLine.push_back(newNode);
			}
			garden.push_back(gardenLine);
		}
		y++;
	}
	inputfile.close();

	uint32_t ID = 0;

	for (int y = 0; y < garden.size(); y++)
	{
		for (int x = 0; x < garden[0].size(); x++)
		{
			if (garden[y][x].id != -1)
			{
				continue;
			}
			GetRegions(garden[y][x], garden, regions, ID);
			ID++;
		}
	}

	std::pair<int, int> MaxBounds(garden.size(), garden[0].size());
	std::unordered_map<uint32_t, int> areas, perimeter, sides;

	for (int i = 0; i < regions.size(); i++)
	{
		areas[regions[i][0].id] = regions[i].size();
		for (int j = 0; j < regions[i].size(); j++)
		{
			int x = regions[i][j].location.second;
			y = regions[i][j].location.first;
			char Ptype = garden[y][x].plantType;

			if (IsOutOfBounds(std::pair<int, int>(y - 1, x), MaxBounds) ||
				garden[y - 1][x].plantType != Ptype)
			{
				perimeter[regions[i][0].id]++;
			}
			if (IsOutOfBounds(std::pair<int, int>(y + 1, x), MaxBounds) ||
				garden[y + 1][x].plantType != Ptype)
			{
				perimeter[regions[i][0].id]++;
			}
			if (IsOutOfBounds(std::pair<int, int>(y, x - 1), MaxBounds) ||
				garden[y][x - 1].plantType != Ptype)
			{
				perimeter[regions[i][0].id]++;
			}
			if (IsOutOfBounds(std::pair<int, int>(y, x + 1), MaxBounds) ||
				garden[y][x + 1].plantType != Ptype)
			{
				perimeter[regions[i][0].id]++;
			}
		}
	}
	for (auto& id : areas)
	{
		TotalPrice += areas[id.first] * perimeter[id.first];
	}

	std::cout << "Part 1: The total price for fences in this garden is: " << TotalPrice << "\n";

    // Part 2
	TotalPrice = 0;
	for (int y = 0; y < garden.size(); y++)
	{
		for (int x = 0; x < garden[y].size(); x++)
		{
			char Ptype = garden[y][x].plantType;

			if (IsOutOfBounds(std::pair<int, int>(y, x - 1), MaxBounds) || garden[y][x - 1].plantType != Ptype)
			{
				garden[y][x].leftSide = true;
				if (IsOutOfBounds(std::pair<int, int>(y - 1, x), MaxBounds)
					|| garden[y - 1][x].plantType != Ptype
					|| !garden[y - 1][x].leftSide)
				{
					sides[garden[y][x].id]++;
				}
			}

			if (IsOutOfBounds(std::pair<int, int>(y, x + 1), MaxBounds) || garden[y][x + 1].plantType != Ptype)
			{
				garden[y][x].rightSide = true;
				if (IsOutOfBounds(std::pair<int, int>(y - 1, x), MaxBounds)
					|| garden[y - 1][x].plantType != Ptype
					|| !garden[y - 1][x].rightSide)
				{
					sides[garden[y][x].id]++;
				}
			}

			if (IsOutOfBounds(std::pair<int, int>(y - 1, x), MaxBounds) || garden[y - 1][x].plantType != Ptype)
			{
				garden[y][x].upSide = true;
				if (IsOutOfBounds(std::pair<int, int>(y, x - 1), MaxBounds)
					|| garden[y][x - 1].plantType != Ptype
					|| !garden[y][x - 1].upSide)
				{
					sides[garden[y][x].id]++;
				}
			}

			if (IsOutOfBounds(std::pair<int, int>(y + 1, x), MaxBounds) || garden[y + 1][x].plantType != Ptype)
			{
				garden[y][x].downSide = true;
				if (IsOutOfBounds(std::pair<int, int>(y, x - 1), MaxBounds)
					|| garden[y][x - 1].plantType != Ptype
					|| !garden[y][x - 1].downSide)
				{
					sides[garden[y][x].id]++;
				}
			}
		}
	}
	for (auto& id : areas)
	{
		TotalPrice += areas[id.first] * sides[id.first];
	}

	std::cout << "Part 2: The total price for fences in this garden is: " << TotalPrice << "\n";
}

void GetRegions(node p1, std::vector<std::vector<node>> &garden, std::vector<std::vector<node>>& regions, uint32_t ID)
{
	std::queue<node> CurrentList;
	std::vector<node> NewRegion;

	/* mark the og as seen */
	p1.id = garden[p1.location.first][p1.location.second].id = ID;
	CurrentList.push(p1);

	while (CurrentList.size() > 0)
	{
		node current = CurrentList.front();
		CurrentList.pop();
		NewRegion.push_back(current);

		GetMatchingPlantNeigbours(current, garden, CurrentList);
	}

	regions.push_back(NewRegion);
}

void GetMatchingPlantNeigbours(node p1, std::vector<std::vector<node>>& garden, std::queue<node>& CurrentList)
{
	std::pair<int, int> MaxBounds(garden.size(), garden[0].size());

	int y = p1.location.first, x = p1.location.second;

	if (!IsOutOfBounds(std::pair<int, int>(y, x - 1), MaxBounds) &&
		garden[y][x - 1].plantType == p1.plantType && garden[y][x - 1].id == -1)
	{
		garden[y][x - 1].id = p1.id;
		CurrentList.push(garden[y][x - 1]);
	}
	if (!IsOutOfBounds(std::pair<int, int>(y, x + 1), MaxBounds) &&
		garden[y][x + 1].plantType == p1.plantType && garden[y][x + 1].id == -1)
	{
		garden[y][x + 1].id = p1.id;
		CurrentList.push(garden[y][x + 1]);
	}
	if (!IsOutOfBounds(std::pair<int, int>(y-1, x), MaxBounds) &&
		garden[y-1][x].plantType == p1.plantType && garden[y - 1][x].id == -1)
	{
		garden[y - 1][x].id = p1.id;
		CurrentList.push(garden[y - 1][x]);
	}
	if (!IsOutOfBounds(std::pair<int, int>(y+1, x), MaxBounds) &&
		garden[y + 1][x].plantType == p1.plantType && garden[y + 1][x].id == -1)
	{
		garden[y + 1][x].id = p1.id;
		CurrentList.push(garden[y + 1][x]);
	}

	return;
}

#define BUTTONACOST 3
#define BUTTONBCOST 1
void DayThirteenSolutions(std::string input)
{
	std::vector<machine> machines;
	unsigned long long int TotalTokensCost = 0;
	std::regex const ButtonAReg("Button A: X\\+([0-9]+), Y\\+([0-9]+)");
	std::regex const ButtonBReg("Button B: X\\+([0-9]+), Y\\+([0-9]+)");
	std::regex const PrizeReg("Prize: X=([0-9]+), Y=([0-9]+)");

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	machine newMachine;
	std::string line;
	std::smatch m;
	while (std::getline(inputfile, line))
	{
		if (std::regex_match(line, m, ButtonAReg))
		{
			newMachine.buttonA.first = std::stoi(m[1]);
			newMachine.buttonA.second = std::stoi(m[2]);
		}
		else if (std::regex_match(line, m, ButtonBReg))
		{
			newMachine.buttonB.first = std::stoi(m[1]);
			newMachine.buttonB.second = std::stoi((m[2]));
		}
		else if (std::regex_match(line, m, PrizeReg))
		{
			newMachine.TargetLocation.first = std::stoi(m[1]);
			newMachine.TargetLocation.second = std::stoi(m[2]);
			machines.push_back(newMachine);
		}
	}
	inputfile.close();

	for (int i = 0; i < machines.size(); i++)
	{
		int D = (machines[i].buttonA.first * machines[i].buttonB.second) -
			(machines[i].buttonB.first * machines[i].buttonA.second);

		int DX = (machines[i].TargetLocation.first * machines[i].buttonB.second) -
			(machines[i].TargetLocation.second * machines[i].buttonB.first);

		int DY = (machines[i].TargetLocation.second * machines[i].buttonA.first) - 
			(machines[i].TargetLocation.first * machines[i].buttonA.second);

		if (DX % D != 0 ||
			DY % D != 0)
		{
			std::cout << "No solution avaliable for current machine index" << i << "\n";
		}
		else
		{
			int A = DX / D;
			int B = DY / D;
			TotalTokensCost += (A * BUTTONACOST) + (B * BUTTONBCOST);
		}
	}

	std::cout << "The fewest tokens you would have to spend to win all possible prizes is " << TotalTokensCost << "(P1)\n";
	TotalTokensCost = 0;

	for (int i = 0; i < machines.size(); i++)
	{
		long long int D = (machines[i].buttonA.first * machines[i].buttonB.second) -
			(machines[i].buttonA.second * machines[i].buttonB.first);

		long long int DX = ((machines[i].TargetLocation.first + 10000000000000) * machines[i].buttonB.second) -
			((machines[i].TargetLocation.second + 10000000000000) * machines[i].buttonB.first);

	    long long int DY = ((machines[i].TargetLocation.second + 10000000000000) * machines[i].buttonA.first) -
			((machines[i].TargetLocation.first + 10000000000000) * machines[i].buttonA.second);

		if (DX % D != 0 ||
			DY % D != 0)
		{
			std::cout << "No solution avaliable for current machine index" << i << "\n";
		}
		else
		{
			long long int A = DX / D;
			long long int B = DY / D;
			TotalTokensCost += (A * BUTTONACOST) + (B * BUTTONBCOST);
		}
	}

	std::cout << "The fewest tokens you would have to spend to win all possible prizes is " << TotalTokensCost << "(P2)\n";

}

void DayFourteenSolution(std::string input)
{
	std::vector<Robot> Robots;
	const int Width = 101, Height = 103;

	std::ifstream inputfile(input);
	if (!inputfile)
	{
		std::cout << "Can not open input file" << input << "\n";
		return;
	}

	std::string line;
	while (std::getline(inputfile, line))
	{
		Robot newRobot;
		for (int i = 0; i < line.size(); i++)
		{
			newRobot.Location.first = std::stoi(line.substr(line.find("p=")+2));
			newRobot.Location.second = std::stoi(line.substr(line.find(',') + 1));

			std::string secondPart = line.substr(line.find("v="), sizeof(line));
			newRobot.velocity.first = std::stoi(secondPart.substr(secondPart.find("v=") + 2));
			newRobot.velocity.second = std::stoi(secondPart.substr(secondPart.find(",") + 1));
		}

		Robots.push_back(newRobot);
	}
	inputfile.close();

	DayFourteenP1(100, Robots, Width, Height);
	// Chinese Remainder Theorem
	DayFourteenP2(6493, Robots, Width, Height);
}

void DayFourteenP1(const int seconds, std::vector<Robot> Robots, const int Width, const int Height)
{
	int SaftyFactor = 0;
	int TL = 0, TR = 0, BL = 0, BR = 0;
	for (int i = 0; i < Robots.size(); i++)
	{
		std::pair<int, int> newpos = Robots[i].Location;
		newpos.first += Robots[i].velocity.first * seconds;
		newpos.second += Robots[i].velocity.second * seconds;

		if (newpos.first < 0)
		{
			int temp = std::ceil((float)-newpos.first / (float)Width);
			newpos.first = (Width * temp) - -newpos.first;
		}
		else
		{
			newpos.first %= Width;
		}

		if (newpos.second < 0)
		{
			int temp = std::ceil((float)-newpos.second / (float)Height);
			newpos.second = (Height * temp) - -newpos.second;
		}
		else
		{
			newpos.second %= Height;
		}
		Robots[i].Location = newpos;


		if (Robots[i].Location.first < (Width / 2))
		{
			if (Robots[i].Location.second < (Height / 2))
			{
				TL++;
			}
			else if (Robots[i].Location.second > (Height / 2))
			{
				BL++;
			}
		}
		else if (Robots[i].Location.first > (Width / 2))
		{
			if (Robots[i].Location.second < (Height / 2))
			{
				TR++;
			}
			else if (Robots[i].Location.second > (Height / 2))
			{
				BR++;
			}
		}
	}

	SaftyFactor = TL * TR * BL * BR;
	std::cout << "P1: The Safty Factor is " << SaftyFactor << "\n";
}

void DayFourteenP2(const int seconds, std::vector<Robot> Robots, const int Width, const int Height)
{
	std::vector<std::vector<char>> Map(Height);
	for (int i = 0; i < Height; i++)
	{
		Map[i].resize(Width);
	}

	for (int i = 1; i <= seconds; i++)
	{
		std::vector<std::vector<char>> Map(Height);
		std::fill(Map.begin(), Map.end(), std::vector<char>(Width, '.'));

		for (int j = 0; j < Robots.size(); j++)
		{
			std::pair<int, int> newpos = Robots[j].Location;
			newpos.first += Robots[j].velocity.first;
			newpos.second += Robots[j].velocity.second;

			if (newpos.first < 0) {
				int temp = std::ceil((float)-newpos.first / (float)Width);
				newpos.first = (Width * temp) - -newpos.first;
			}
			else { 
				newpos.first %= Width; 
			}
			if (newpos.second < 0) {
				int temp = std::ceil((float)-newpos.second / (float)Height);
				newpos.second = (Height * temp) - -newpos.second;
			}
			else {
				newpos.second %= Height;
			}

			Robots[j].Location = newpos;
			Map[Robots[j].Location.second][Robots[j].Location.first] = '#';
		}


		if (i == seconds) 
		{
			std::cout << "Seconds: " << i << "\n";
			for (int j = 0; j < Map.size(); j++)
			{
				std::copy(Map[j].begin(), Map[j].end(),
					std::ostream_iterator<char>(std::cout, ""));
				std::cout << "\n";
			}
			std::cin.get();
			system("cls");
		}
	}
}

void DayFiveteenSolution(std::string input)
{
	std::vector<std::vector<char>> Map;
	std::vector<std::vector<char>> MapP2;
	std::vector<char> moves;
	std::pair<int, int> PLMap1, PLMap2;
	bool bOnMoveInstructions = false;

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
			bOnMoveInstructions = true;
		}

		if (bOnMoveInstructions)
		{
			for (auto move : line)
			{
				moves.push_back(move);
			}
		}
		else
		{
			std::vector<char> newLine;
			std::vector<char> newLineP2;
			for (int x = 0; x < line.size(); x++)
			{
				if (line[x] == '@')
				{
					PLMap1 = std::pair<int, int>(Map.size(), newLine.size());
					PLMap2 = std::pair<int, int>(MapP2.size(), newLineP2.size());
					newLineP2.push_back(line[x]);
					newLineP2.push_back('.');
				}
				else if (line[x] == 'O')
				{
					newLineP2.push_back('[');
					newLineP2.push_back(']');
				}
				else
				{
					newLineP2.push_back(line[x]);
					newLineP2.push_back(line[x]);
				}
				newLine.push_back(line[x]);
			}
			Map.push_back(newLine);
			MapP2.push_back(newLineP2);
		}
	}
	inputfile.close();

	//DayFiveteenSolve(Map, moves, PLMap1, false);
	DayFiveteenSolve(MapP2, moves, PLMap2, true);
}


void DayFiveteenSolve(std::vector<std::vector<char>>& Map, std::vector<char> moves, std::pair<int, int> playerLocation, bool bAreBoxesWide)
{
	std::pair<int, int> NextFreeLocation, NextMove;
	bool StartBarrel = false;

	for (int i = 0; i < moves.size(); i++)
	{
		switch (moves[i])
		{
		case '^':
			NextMove = std::pair<int, int>(-1, 0);
			break;
		case '>':
			NextMove = std::pair<int, int>(0, 1);
			break;
		case '<':
			NextMove = std::pair<int, int>(0, -1);
			break;
		case 'v':
			NextMove = std::pair<int, int>(1, 0);
			break;
		default:
			std::cout << "How did '" << moves[i] << "' get here!!!!????";
			return;
			break;
		}

		if (!bAreBoxesWide || NextMove.second != 0)
		{
			NormalPlayerTravers(Map, playerLocation, NextMove);
		}
		else
		{
			StackPlayerTravers(Map, playerLocation, NextMove);
		}
	}

	PrintMap(Map, false);
	std::cout << "The sum of all boxes' GPS coordinates is: " << GetFinalScore(Map) << "\n";
}

void NormalPlayerTravers(std::vector<std::vector<char>>& Map, std::pair<int, int> &playerLocation, std::pair<int, int> move)
{
	std::vector<MapObjectInfo> barrels;
	std::pair<int, int> NewPlayerLocation, NextFreeLocation;
	int thingToMove = 0;

	NextFreeLocation = GetNextFreeLocation(Map, playerLocation, move, barrels);
	thingToMove = barrels.size() + 1; // add player

	// -1,-1 means nothing to do
	if (NextFreeLocation != std::pair<int, int>(-1, -1))
	{
		while (NextFreeLocation != playerLocation)
		{
			if (thingToMove > 0)
			{
				if (barrels.size() > 0)
				{
					if (barrels[barrels.size() - 1].FirstIconSaw == 'O')
					{
						Map[NextFreeLocation.first][NextFreeLocation.second] = 'O';
						barrels.pop_back();
					}
					else
					{
						if (move.second == -1)
						{
							Map[NextFreeLocation.first][NextFreeLocation.second] = '[';
							NextFreeLocation = NextFreeLocation - move;
							Map[NextFreeLocation.first][NextFreeLocation.second] = ']';
						}
						else 
						{
							Map[NextFreeLocation.first][NextFreeLocation.second] = ']';
							NextFreeLocation = NextFreeLocation - move;
							Map[NextFreeLocation.first][NextFreeLocation.second] = '[';
						}
						barrels.pop_back();
					}
				}
				else
				{
					Map[NextFreeLocation.first][NextFreeLocation.second] = '@';
					NewPlayerLocation = NextFreeLocation;
				}
				thingToMove--;
			}
			else
			{
				Map[NextFreeLocation.first][NextFreeLocation.second] = '.';
			}
			NextFreeLocation = NextFreeLocation - move;
		}
		Map[playerLocation.first][playerLocation.second] = '.';
		playerLocation = NewPlayerLocation;
	}

}

void StackPlayerTravers(std::vector<std::vector<char>>& Map, std::pair<int, int>& playerLocation, std::pair<int, int> move)
{
	std::pair<int, int> ObjectLocation, NewLocation;
	std::stack<MapObjectInfo> ObjectsToMove;
	MapObjectInfo currentObject;
	std::vector<std::vector<char>> MapCopy = Map;
	ObjectsToMove.push(MapObjectInfo(Map[playerLocation.first][playerLocation.second], playerLocation, false));

	while (ObjectsToMove.size() > 0)
	{
		currentObject = ObjectsToMove.top();
		ObjectLocation = currentObject.Postion;
		NewLocation = ObjectLocation + move;

		if (Map[NewLocation.first][NewLocation.second] == '#') // Hit a wall, wont be able to move 
		{
			Map = MapCopy;
			break;
		}

		if (!currentObject.bWideObject) // for the Player
		{
			if (Map[NewLocation.first][NewLocation.second] == '.')
			{
				ObjectsToMove.pop();
				Map[NewLocation.first][NewLocation.second] = currentObject.FirstIconSaw;
				Map[playerLocation.first][playerLocation.second] = '.';
				playerLocation = NewLocation;
			}
			else
			{
				if (Map[NewLocation.first][NewLocation.second] == ']')
				{
					NewLocation.second -= 1;
				}
				MapObjectInfo NewObject = MapObjectInfo(Map[NewLocation.first][NewLocation.second], NewLocation, true);
				ObjectsToMove.push(NewObject);
			}
		}
		else
		{
			if(Map[NewLocation.first][NewLocation.second+1] == '#') // Hit a wall, wont be able to move 
			{
				Map = MapCopy;
				break;
			}
			else if(Map[NewLocation.first][NewLocation.second] == '.' && 
				Map[NewLocation.first][NewLocation.second + 1] == '.')
			{
				ObjectsToMove.pop();
				Map[NewLocation.first][NewLocation.second] = '[';
				Map[NewLocation.first][NewLocation.second + 1] = ']';
				Map[ObjectLocation.first][ObjectLocation.second] = '.';
				Map[ObjectLocation.first][ObjectLocation.second+1] = '.';
			}
			else // we have hit another box, add it to the stack
			{
				if (Map[NewLocation.first][NewLocation.second] == ']')
				{
					NewLocation.second -= 1;
				}
				else if (Map[NewLocation.first][NewLocation.second] == '.')
				{
					NewLocation.second += 1;
				}
				MapObjectInfo NewObject = MapObjectInfo(Map[NewLocation.first][NewLocation.second], NewLocation, true);
				ObjectsToMove.push(NewObject);
			}
		}
	}
}

std::pair<int, int> GetNextFreeLocation(std::vector<std::vector<char>>& Map, std::pair<int, int> playerLocation, std::pair<int, int> direction, std::vector<MapObjectInfo>& Barrels)
{
	std::pair<int, int> FreeLocation = playerLocation;
	bool bFoundFreeSpot = false;
	Barrels.clear();

	while (!IsOutOfBounds(FreeLocation, std::pair<int,int>(Map.size(), Map[0].size()))
		&& !bFoundFreeSpot)
	{
		FreeLocation = FreeLocation + direction;

		if (Map[FreeLocation.first][FreeLocation.second] == '.')
		{
			bFoundFreeSpot = true;
			break;
		}
		else if (Map[FreeLocation.first][FreeLocation.second] == '#')
		{
			//Cant move anywhere
			break;
		}
		else if (Map[FreeLocation.first][FreeLocation.second] == 'O')
		{
			Barrels.push_back(MapObjectInfo('O', FreeLocation, false));
		}
		else if (Map[FreeLocation.first][FreeLocation.second] == '[' ||
			Map[FreeLocation.first][FreeLocation.second] == ']')
		{
			if (direction.first != 0)
			{
				Barrels.push_back(MapObjectInfo(Map[FreeLocation.first][FreeLocation.second], FreeLocation, true));
			}
			else
			{
				if (direction.second == 1 && Map[FreeLocation.first][FreeLocation.second] == '[')
				{
					Barrels.push_back(MapObjectInfo('[', FreeLocation, true));
				}
				else if (direction.second == -1 && Map[FreeLocation.first][FreeLocation.second] == ']')
				{
					Barrels.push_back(MapObjectInfo(']', FreeLocation, true));
				}
			}
		}
	}

	if (!bFoundFreeSpot)
	{
		FreeLocation = std::pair<int, int>(-1, -1);
	}

	return FreeLocation;
}

int GetFinalScore(std::vector<std::vector<char>> Map)
{
	int FinalScore = 0;
	for (int y = 1; y < Map.size() - 1; y++)
	{
		for (int x = 1; x < Map[0].size() - 1; x++)
		{
			if (Map[y][x] == 'O') 
			{
				FinalScore += ((100 * y) + x);
			}

			if  (Map[y][x] == '[')
			{
				FinalScore += ((100 * y) + x);
				x++; // Skip ]
			}
		}
	}

	return FinalScore;
}


