#include "Knight.h"
/* ---------- Move Functions ---------- */
bool Knight::canSee(int to_row, int to_col, Piece* board[8][8]) {
  // Check if the row_difference is -1/1 and col_difference is -2/2
  // or vice versa:
  int row_difference = to_row - row;
  int col_difference = to_col - col;
  if (row_difference == 1 || row_difference == -1) {
    if (col_difference == 2 || col_difference == -2) {return true;}
  }
  if (col_difference == 1 || col_difference == -1) {
    if (row_difference == 2 || row_difference == -2) {return true;}
  }
  // Return true!
  return false;
}

/* ---------- Printers ---------- */
void Knight::printPiece1() {std::cout << "   ";}
void Knight::printPiece2() {std::cout << "(\"\\";}
void Knight::printPiece3() {std::cout << ")" << (is_white ? " " : "#") << "'";}
void Knight::printPiece4() {std::cout << "/" << (is_white ? " " : "#") << "\\";}
void Knight::printPiece5() {std::cout << "===";}
