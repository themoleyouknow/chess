#include "Rook.h"
/* Other Functions */
bool Rook::canSee(int to_row, int to_col, Piece* board[8][8]) {
  // Check if the move is horizontal or not:
  int row_difference = to_row - row;
  int col_difference = to_col - col;
  if (row_difference != 0 && col_difference != 0) {
    return false;
  }
  // Check if there is anything between this piece and the proposed board location:
  int row_count, col_count;
  int check_count, check_difference;
  if (row_difference == 0) {
    row_count = 0;
    col_count = (col_difference<0 ? -1 : 1);
    check_count = col_count;
    check_difference = col_difference;
  }
  else {
    row_count = (row_difference<0 ? -1 : 1);
    check_count = row_count;
    check_difference = row_difference;
    col_count = 0;
  }
  for (int count = 1; count < check_count*check_difference; ++count) {
    if (board[row + row_count*count][col + col_count*count] != nullptr) {return false;}
  }
  // Return true!
  return true;
}

/* ---------- Printers ---------- */
void Rook::printPiece1() {std::cout << "   ";}
void Rook::printPiece2() {std::cout << "uuu";}
void Rook::printPiece3() {std::cout << "|" << (is_white ? " " : "#") << "|";}
void Rook::printPiece4() {std::cout << "|" << (is_white ? " " : "#") << "|";}
void Rook::printPiece5() {std::cout << "===";}
