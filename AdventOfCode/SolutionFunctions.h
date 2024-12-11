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