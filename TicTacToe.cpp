//compiled with 'g++ -std=c++17 TicTacToe.cpp'

#include <iostream>
#include <array>
#include <vector>
#include <climits>

#include "Board.hpp"

using namespace std;

int nodesEvaluated = 0;

class AIPlayer {
public:
	AIPlayer(Piece p) : my_piece(p) {
		if (my_piece == X) opponent_piece = O;
		else opponent_piece = X;
	}

	/**
	 * given a board, this method scores a set of moves using the minimax algorithm 
	 * 
	 * it iterates through a container of the possible moves,
	 * creating a copy of the board for each and scoring it using the minimax algorithm
	 * 
	 * returns the highest scoring move 
	 */
	int getMove(const Board& b) {
		int bestMove = -1;
		int score, bestScore = INT_MIN;

		for (int move : getValidMoves(b)) {
			Board b2 (b);
			b2.setPiece(move, my_piece);
			score = minimax(b2, 5, false);

			if (score > bestScore) {
				bestScore = score;
				bestMove = move;
			}
		}

		nodesEvaluated = 0;

		cout << "Best score: " << bestScore << endl;

		return bestMove;
	}

private:
	Piece my_piece, opponent_piece;

	/**
	 * the minimax algorithm is a standard algorithm for turn based games
	 * that uses a search tree to look ahead and determine the best move
	 * 
	 * it is abstracted by using a method scoreBoard() that returns a 
	 * static analysis of the board and a method that returns a container
	 * of the moves it can try (getValidMoves() or getUniqueMoves()) 
	 */
	int minimax(Board b, int depth, bool maximizing) {
		//cout << "Nodes Evaluate: " << ++nodesEvaluated << endl;

		if (depth == 0 || b.isGameOver()) {
			return scoreBoard(b);
		}

		int eval, curEval;

		if (maximizing) {
			eval = INT_MIN;
			for (int move : getValidMoves(b)) {
				Board b2 (b);
				b2.setPiece(move, my_piece);
				curEval = minimax(b2, depth - 1, false);
				eval = max(eval, curEval);
			}
			return eval;
		} else { // minimizing
			eval = INT_MAX;
			for (int move : getValidMoves(b)) {
				Board b2 (b);
				b2.setPiece(move, opponent_piece);
				curEval = minimax(b2, depth - 1, true);
				eval = min(eval, curEval);
			}
			return eval;
		}
	}

	/**
	 * tests a board for symmetry on the horizontal and vertical symmetry
	 * 
	 * This method can be used in place for the getValidMoves as it has the same param and return
	 *
	 * it is used to reduce score calculations on two tiles that are symmetrical
	 * and thus would return the same score.
	 * 
	 * returns a vector of all the unique valid moves.
	 */
	vector<int> getUniqueMoves(const Board& b) {
		bool vertSym = true, horzSym = true;
		vector<int> moves;

		for (int i = 0; i < 3; i++) {
			if (vertSym) vertSym &= (b.getPiece(0, i) == b.getPiece(2, i));
			if (horzSym) horzSym &= (b.getPiece(i, 0) == b.getPiece(i, 2));
		}

		if (b.isValidMove(1))                         moves.push_back(1);
		if (b.isValidMove(2))                         moves.push_back(2);
		if (b.isValidMove(3) && !vertSym)             moves.push_back(3);
		if (b.isValidMove(4))                         moves.push_back(4);
		if (b.isValidMove(5))                         moves.push_back(5);
		if (b.isValidMove(6) && !vertSym)             moves.push_back(6);
		if (b.isValidMove(7) && !horzSym)             moves.push_back(7);
		if (b.isValidMove(8) && !horzSym)             moves.push_back(8);
		if (b.isValidMove(9) && !vertSym && !horzSym) moves.push_back(9);

		return moves;
	}

	/**
	 * returns a vector of all positions that are a valid move i.e. empty
	 */
	vector<int> getValidMoves(const Board& b) {
		vector<int> moves;
		for (int i = 1; i <= 9; i++) {
			if (b.getPiece(i) == E) moves.push_back(i);
		}
		return moves;
	}

	/** 
	 * used by the AIPLayer to get a static analysis of the board
	 */
	int scoreBoard(const Board& b) {
		if (b.getWinner() == Invalid) { // means tie
			return 0;
		} else if (b.getWinner() == my_piece) {
			return 1;
		} else {
			return -1;
		}
	}
};

// new line 		- \n
// erase display 	- \033[2J
// erase line 		- \033[K
// cursor up 		- \033[<N>A
// cursor down 		- \033[<N>B
// cursor forwards 	- \033[<N>C
// cursor backwards - \033[<N>D
// position cursor  - \033[<L>;<C>H

int main() {
	Board b;
	AIPlayer pc (X);

	while (!b.isGameOver()) {
		int pcMove = pc.getMove(b);
		cout << pcMove << endl;
		b.setPiece(pc.getMove(b), X);

		if (b.isGameOver()) break;

		b.print();
		int n;
		cin >> n;
		b.setPiece(n, O);
		b.print();
	}

	cout << "Game Over!" << endl;

	b.print();
	

	return 0;
}