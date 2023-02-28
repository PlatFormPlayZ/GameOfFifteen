#pragma once
#include <vector>

// char int pair that represents a cell on the board
typedef std::pair<const char, int> boardCell;

class board
{
public:
	//turn enum
	enum class player { Even, Odd };

	//construtctor
	board();
	virtual ~board();

	//methods the board has
	int calculateBoardValue();
	player getTurn();
	std::vector<int> getOptions();
	boardCell getRecommendedMove();
	void makeMove(boardCell move);

private:
	//values
	boardCell cells[9] = {std::make_pair('a', 0), std::make_pair('b', 0), std::make_pair('c', 0), 
								std::make_pair('d', 0), std::make_pair('e', 0), std::make_pair('f', 0), 
									std::make_pair('g', 0), std::make_pair('h', 0), std::make_pair('i', 0) };
	int boardValue;
	player turn;
};