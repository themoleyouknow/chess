#include "Piece.h"
/* -------------------- Move Checkers -------------------- */
bool Piece::isValidMove(int to_row, int to_col, Piece *board[8][8]) {
  // Check if proposed board location contains a piece of the same colour as this one:
  if (!isLegal(to_row, to_col, board)) {
    return false;}
  // Check if this piece can see the proposed board location:
  if (!canSee(to_row, to_col, board)) {
    return false;
  }
  // Return true!
  return true;
}
bool Piece::isLegal(int to_row, int to_col, Piece* board[8][8]) {
  // Check if on board:
  if (to_row < 0 || to_row > 7 || to_col < 0 || to_col > 7) {
    return false;
  }
  // Check if not empty, and if on same team:
  if (board[to_row][to_col] != nullptr && !(board[to_row][to_col]->getIsWhite()^is_white)) {
    return false;
  }
  return true;
}
bool Piece::canMove(Piece *board[8][8]) {
  // Iterate over board to see if there are any valid moves that can be made:
  for (int count1 = 0; count1 < 8; ++count1) {
    for (int count2 = 0; count2 < 8; ++count2) {
	if (isValidMove(count1, count2, board)) {
	    return true;
	}
    }
  }
}
