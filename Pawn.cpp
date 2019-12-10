#include "Pawn.h"
/* ---------- Move Functions ---------- */
bool Pawn::canSee(int to_row, int to_col, Piece *board[8][8]) {
  // Check if the move is doable or not for a pawn:
  int row_difference = to_row - row;
  int col_difference = to_col - col;
  // Check if we'll be jumping two rows, make sure we haven't moved yet
  // and that the space in between is empty:
  if (row_difference == 2 || row_difference == -2) {
    if (col_difference !=0 || has_moved) {
      return false;
    }
    if ((row_difference > 0 && board[row + 1][col] != nullptr) ||
	(row_difference < 0 && board[row - 1][col] != nullptr)) {
      return false;
    }
  }else { // Otherwise check for regular moves!
    if (is_white) {
      if (row_difference != -1 ||
	  (col_difference != 0 && col_difference != 1 && col_difference != -1)) {
        return false;
      }
    }else {
      if (row_difference !=  1 ||
	  (col_difference != 0 && col_difference != 1 && col_difference != -1)) {
        return false;
      }
    }
  }
  // Check if we're trying to move diagonally, and there's nothing there:
  if (col_difference == 0) {
    if (board[to_row][to_col] != nullptr) {
      return false;
    }
  }else {
    if (board[to_row][to_col] == nullptr) {
      return false;}
  }
    
  // Return true!
  return true;
}

/* ---------- Printers ---------- */
void Pawn::printPiece1() {std::cout << "   ";}
void Pawn::printPiece2() {std::cout << "   ";}
void Pawn::printPiece3() {std::cout << " o ";}
void Pawn::printPiece4() {std::cout << "(" << (is_white ? " " : "#") << ")";}
void Pawn::printPiece5() {std::cout << "===";}
