#include "board.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h> 

using namespace std;

board::board() {
	boardValue = 0;
	calculateTurn();
	gameOver = false;
}

board::~board() 
{

}

boardCell board::getRecommendedMove() {
	if (gameOver) { return std::make_pair('n', 0); }
	// Best Logic I can come up with at 5AM
	srand(time(NULL));
	std::vector<boardCell> openCells = getOpenCells();
	std::vector<int> opt = getTurnOptions();
	int cell = rand() % openCells.size();
	int option = rand() % opt.size();
	return std::make_pair(cells[cell].first, opt[option]);
	/*
	for (int i = 0; i < cellGroupings.size(); i++)
	{
		int groupingIndex1 = std::get<0>(cellGroupings[i]);
		int groupingIndex2 = std::get<1>(cellGroupings[i]);
		int groupingIndex3 = std::get<2>(cellGroupings[i]);
		int sum = cells[groupingIndex1].second + cells[groupingIndex2].second + cells[groupingIndex3].second;
		if (sum == 15) { return std::make_pair('w', 100); }
		if ((cells[groupingIndex1].second == 0 || cells[groupingIndex2].second == 0 || cells[groupingIndex3].second == 0) && (sum < 15))
		{
			return std::make_pair('z', -1);
		}
	}
	return std::make_pair('z', -1);
	*/
}

int board::calculateBoardValue() {
	return 0;
}

board::player board::getTurn() {
	return turn;
}

std::vector<int> board::getTurnOptions() {
	std::vector<int> opts;
	for (int i = 0; i < options.size(); i++)
	{
		if (options[i] % 2 == static_cast<int>(turn))
		{
			opts.push_back(options[i]);
		}
	}
	return opts;
}

void board::makeMove(boardCell move) 
{
	board::player unsetPlayer;
	bool fail = true;
	if (validOption(move.second) && !gameOver)
	{
		int size = cells.size();
		for (int i = 0; i < size; i++) 
		{
			if (cells[i].first == move.first)
			{
				cells[i].second = move.second;
				removeOption(move.second);
				trySetWinner(move.second);
				fail = false;
			}
		}
	}
	if (fail) { std::cout << "[board.cpp - makemove()] - failed to insert unexepcted... tried to insert on [" << move.first << " , " << move.second << "]" << std::endl; }
}

void board::setBoard(std::string data)
{
	std::vector<std::string> results;
	boost::split(results, data, boost::is_any_of(","));
	if (results.size() != 9) { std::cout << "[board.cpp - setBoard] - expected 9 points of data got: " << results.size() << std::endl; }
	else {
		for (int i = 0; i < results.size(); i++)
		{
			makeMove(std::make_pair(cells[i].first, stoi(results[i])));
			trySetWinner(stoi(results[i]));
		}
		calculateTurn();
	}
}

bool board::validOption(int opt) {
	if (opt == 0) { return true; }
	for (int i = 0; i < options.size(); i++) 
	{
		if (opt == options[i])
		{
			return true;
		}
	}
	return false;
}

void board::trySetWinner(int lastPlay)
{
	if (checkForWin())
	{
		if (lastPlay % 2 == 0)
			winner = player::Even;
		else
			winner = player::Odd;
		gameOver = true;
	}
}

bool board::checkForWin()
{
	for (int i = 0; i < cellGroupings.size(); i++)
	{
		int groupingIndex1 = std::get<0>(cellGroupings[i]);
		int groupingIndex2 = std::get<1>(cellGroupings[i]);
		int groupingIndex3 = std::get<2>(cellGroupings[i]);
		int sum = cells[groupingIndex1].second + cells[groupingIndex2].second + cells[groupingIndex3].second;
		if (sum == 15) 
		{ 
			return true; 
		}
	}
	return false;
}

std::string board::toString()
{
	std::string toStr = "(";
	for (int i = 0; i < cells.size(); i++)
	{
		if(i == 0) { toStr += to_string(cells[i].second); }
		else { toStr += "," + to_string(cells[i].second); }
	}
	toStr += ")";
	std::string additionalMessage = "";
	if (gameOver) 
	{
		additionalMessage += " and ";
		if (static_cast<int>(winner) == 0)
			additionalMessage += "Even";
		else
			additionalMessage += "Odd";
		additionalMessage += " has Won the game!";
	}
	return toStr + additionalMessage;
}

void board::removeOption(int opt)
{
	for (int i = 0; i < options.size(); i++)
	{
		if (options[i] == opt)
		{
			options.erase(options.begin() + i);
		}
	}
}

void board::calculateTurn()
{
	if ((9 - options.size()) % 2 == 0)
	{
		turn = player::Odd;
	}
	else
	{
		turn = player::Even;
	}
}

std::vector<boardCell> board::getOpenCells()
{
	std::vector<boardCell> results;
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].second == 0)
		{
			results.push_back(cells[i]);
		}
	}
	return results;
}
