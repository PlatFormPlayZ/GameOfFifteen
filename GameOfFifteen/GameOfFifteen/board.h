#pragma once
#include <vector>
#include <string>
#include <tuple>

// char int pair that represents a cell on the board
typedef std::pair<const char, int> boardCell;
typedef std::tuple<const int, const int, const int> winningSequence;
typedef std::tuple<const int, const int, const int> cellGrouping;

class board
{
public:
	//turn enum
	enum class player { Even = 0, Odd = 1 };

	//construtctor
	board();
	virtual ~board();

	//methods the board has
	int calculateBoardValue();
	player getTurn();
	std::vector<int> getTurnOptions();
	boardCell getRecommendedMove();
	void makeMove(boardCell move);
	void setBoard(std::string data);
	bool validOption(int opt);
	void trySetWinner(int lastPlay);
	bool checkForWin();
	std::string toString();
	void removeOption(int opt);
	void calculateTurn();
	std::vector<boardCell> getOpenCells();

private:
	//values
	std::vector<boardCell> cells = {std::make_pair('a', 0), std::make_pair('b', 0), std::make_pair('c', 0), 
									std::make_pair('d', 0), std::make_pair('e', 0), std::make_pair('f', 0), 
									std::make_pair('g', 0), std::make_pair('h', 0), std::make_pair('i', 0) };
	const std::vector<winningSequence> sequences = { std::make_tuple(1,5,9), std::make_tuple(1,6,8), std::make_tuple(2,4,9), std::make_tuple(2,5,8), 
													 std::make_tuple(2,6,7), std::make_tuple(3,4,8), std::make_tuple(3,5,7) , std::make_tuple(4,5,6) };
	const std::vector<cellGrouping> cellGroupings = { std::make_tuple(0, 1, 2), std::make_tuple(3, 4, 5), std::make_tuple(6, 7, 8),
													  std::make_tuple(0, 3, 6), std::make_tuple(1, 4, 7), std::make_tuple(2, 5, 8),
													  std::make_tuple(0, 4, 8), std::make_tuple(6, 4, 2) };
	std::vector<int> options = {1,2,3,4,5,6,7,8,9};
	int boardValue;
	player winner;
	bool gameOver;
	player turn;
};