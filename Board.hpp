/*
  for board spaces:
    -1 is invalid or does not exist
     0 is empty
     1 is player 1
     2 is player 2
*/

#include <iostream>
#include <vector>

using namespace std;

class Board {
private:
  int width, height;
  char player1, player2;
  vector<int> board;
  char winner;
  bool gameOver;


public:
  bool player1Turn;

  Board(int w, int h, char p1, char p2) 
    : width(w), height(h), player1(p1), player2(p2) {
    winner = -1;
    gameOver = false;
    player1Turn = true;

    for(int i = 0; i < width * height; i++) board.push_back(0);
  }

  Board(const Board& b2) {
    width = b2.width;
    height = b2.height;
    board = b2.board;
    winner = b2.winner;
    gameOver = b2.gameOver;
    player1Turn = b2.player1Turn;
  }

  bool isInBounds(int n) const { return (n >= 0 && n < width * height); }

  bool isInBounds(int x, int y) const { return (x >= 0 && x < width && y >= 0 && y < height); }

  int getPiece(int n) const {
    if (isInBounds(n)) return board[n];
    else return -1;
  }

  int getPiece(int x, int y) const { return getPiece(x + (3 * y)); }

  bool setPiece(int n, int player) {
    if (isInBounds(n) && (player == 1 || player == 2)) {
      board[n] = player;
      return true;
    } else {
      return false;
    }
  }

  bool setPiece(int x, int y, int player) { return setPiece(x + (3 * y), player); }

  bool isValidMove(int x, int y) const { return (getPiece(x, y) == 0); }

  bool isValidMove(int n) const { return (getPiece(n) == 0); }

  char getWinner() const { return winner; }

  void setWinner(char w) { winner = w; }

  virtual bool isGameOver();

  virtual void print() const;
};