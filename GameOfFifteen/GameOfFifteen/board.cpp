#include "board.h"

using namespace std;

board::board() {
	boardValue = calculateBoardValue();
	turn = getTurn();
}

board::~board() {

}

int board::calculateBoardValue() {
	return 0;
}

board::player board::getTurn() {
	return player::Even;
}

vector<int> board::getOptions() {
	return {0};
}

boardCell board::getRecommendedMove() {
	return std::make_pair('z', -1);
}

void board::makeMove(boardCell move) {

}