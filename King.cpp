#include "King.h"
/* ---------- Move Functions ---------- */
bool King::canSee(int to_row, int to_col, Piece* board[8][8]) {
  // Check if the move is within range:
  int row_difference = to_row - row;
  int col_difference = to_col - col;
  // Check for castling move attempt:
  if ( row_difference == 0 && !has_moved &&
      (col_difference == 2 || col_difference == -2)) {
    // Check if short, and if short side castling possible:
    if (col_difference > 0            &&
	board[row][7] != nullptr      &&
	!board[row][7]->getHasMoved() &&
	board[row][5] == nullptr      &&
	board[row][6] == nullptr      &&
	!underThreat(row, 5, board)   &&
	!underThreat(row, 6, board)  ) {
      return true;
    // Checking if long side castling possible:
    }else if (board[row][0] != nullptr      &&
	      !board[row][0]->getHasMoved() &&
	      board[row][3] == nullptr      &&
	      board[row][2] == nullptr      &&
	      board[row][1] == nullptr      &&	      
	      !underThreat(row, 3, board)   &&
	      !underThreat(row, 2, board)  ) {
      return true;
    }else {return false;}
  }
  // Check for a regular move attempt:
  if (underThreat(to_row, to_col, board)) {return false;}
  if ((row_difference != 1 && row_difference !=-1 && row_difference != 0) ||
      (col_difference != 1 && col_difference !=-1 && col_difference != 0)) {
    return false;
  }
  // Return true!
  return true;
}

bool King::underThreat(int const check_row, int const check_col, Piece* board[8][8]) {
  for (int row_count; row_count < 8; ++row_count) {
    for (int col_count; col_count < 8; ++col_count) {
      if (board[row_count][col_count] != nullptr                                 &&
	  board[row_count][col_count]->getIsWhite()^is_white                     &&
	  board[row_count][col_count]->isValidMove(check_row, check_col, board)) {
	// Return true!
	return true;
      }
    }
  }
  // Return false!
  return false;
}
  

/* ---------- Printers ---------- */
void King::printPiece1() {std::cout << "_+_";}
void King::printPiece2() {std::cout << "\\" << (is_white ? " " : "#") << "/";}
void King::printPiece3() {std::cout << "(" << (is_white ? " " : "#") << ")";}
void King::printPiece4() {std::cout << "/" << (is_white ? " " : "#") << "\\";}
void King::printPiece5() {std::cout << "===";}
