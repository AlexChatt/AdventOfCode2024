#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <queue>
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
void DayNineP1(std::vector<int> file);
void DayNineP2(std::vector<int> file);

void DayTenSolution(std::string input);
int GetTrailHeads(std::pair<int, int> location, std::vector<std::vector<int>> Map, std::set<std::pair<int, int>>& NineSeen, bool bP2);
std::vector<std::pair<int, int>> getValidIncrease(std::pair<int, int> location, std::vector<std::vector<int>> Map);

void DayElevanSolution(std::string input);
void SimulateBlink(std::vector<long long> &stones);
void SimulateBlink(std::unordered_map<long long, long long>& stones);
void addToMap(std::unordered_map<long long, long long>& stones, long long stoneNum, long long stoneCount);

struct node
{
	char plantType;
	int id;
	std::pair<int, int> location;
	bool upSide, leftSide, rightSide, downSide;

	node()
	{
		plantType = '\0';
		id = -1;
		upSide = leftSide =  rightSide = downSide = false;
		location = std::pair<int, int>(-1, -1);
	}

	node(char pType, std::pair<int, int> loc)
	{
		id = -1;
		plantType = pType;
		location = loc;
		upSide = leftSide = rightSide = downSide = false;
	}

};
void DayTwelveSolution(std::string input);
void GetRegions(node p1, std::vector<std::vector<node>>& garden, std::vector<std::vector<node>>& regions, uint32_t ID);
void GetMatchingPlantNeigbours(node p1, std::vector<std::vector<node>>& garden, std::queue<node>& CurrentList);