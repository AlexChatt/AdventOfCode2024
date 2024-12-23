#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include "Utility.h"

void DayOneSolution(std::string input);

void DayTwoSolution(std::string input);
bool CheckValidSequence(std::vector<int> Sequence, int& problemIndex, bool bisAscending, int ignoreElement);

void DayThreeSolution(std::string input);

void DayFourSolution(std::string input);
int GetXmasMatchesP1(std::vector<std::vector<char>> grid, const int x, const int y);
bool GetXmasMatchesP2(std::vector<std::vector<char>> grid, const int x, const int y);

void DayFiveSolution(std::string input);
bool checkIfSequenceValid(std::vector<int> sequence, std::unordered_map<int, std::set<int>> Rules);
int FixInvalidSequence(std::vector<int> &sequence, std::unordered_map<int, std::set<int>> Rules);
bool checkNumbersValid(std::set<int> InvalidNums, std::vector<int> NumsSeen, int& NumsSeenIndex);

enum direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};
struct visitedPoints
{
	std::pair<int, int> location;
	int dir = 0;

	visitedPoints(int x, int y, int d)
	{
		location = {x, y};
		dir = d;
	}

	bool operator<(const visitedPoints& other) const
	{
		if (location < other.location) return true;
		if (location > other.location) return false;
		return dir < other.dir;
	}
	bool operator=(const visitedPoints& other) const
	{
		return location == other.location && dir == other.dir;
	}
};
void DaySixSolution(std::string input);
bool RouteTraverse(std::vector<std::vector<char>> map, std::pair<int, int> playerPos, int playerDir, std::vector<std::pair<int,int>>& visitedLocation);

void DaySevenSolution(std::string input);
bool RecursiveSolve(long long int TargetNum, std::vector<int> numbers, int index, long long int sumSoFar);


struct antenna
{
	bool bIsAntinode = false;
	std::pair<int, int> position;
};
void DayEightSolution(std::string input);
int GetAntennaPoints(std::vector<antenna> antentas, std::vector<std::vector<bool>>& map);

void DayNineSolution(std::string input);