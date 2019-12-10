#include "Bishop.h"
/* ---------- Move Functions ---------- */
bool Bishop::canSee(int to_row, int to_col, Piece *board[8][8]) {
  // Check if the move is diagonal or not:
  int row_difference = to_row - row;
  int col_difference = to_col - col;
  if ((row_difference == 0 || col_difference == 0) ||
      (row_difference != col_difference &&
       row_difference != col_difference*-1)) {
    return false;
  }
  // Check if there is anything between this piece and the proposed board location:
  int row_count = (row_difference<0 ? -1 : 1);
  int col_count = (col_difference<0 ? -1 : 1);
  for (int count = 1; count < row_count*row_difference; ++count) {
    if (board[row + row_count*count][col + col_count*count] != nullptr) {return false;}
  }
  // Return true!
  return true;
}

/* ---------- Printers ---------- */
void Bishop::printPiece1() {std::cout << "   ";}
void Bishop::printPiece2() {std::cout << " 0 ";}
void Bishop::printPiece3() {std::cout << "(" << (is_white ? " " : "#") << ")";}
void Bishop::printPiece4() {std::cout << "/" << (is_white ? " " : "#") << "\\";}
void Bishop::printPiece5() {std::cout << "===";}
