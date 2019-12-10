#include "Piece.h"

class King : public Piece {
 public:
  // Constructor (uses Piece):
  King(std::string name, bool is_white, int row, int col) : Piece(name, is_white, row, col) {}
  // Move Functions:
  bool canSee(int row, int col, Piece* board[8][8]) override;
  bool underThreat(int const check_row, int const check_col, Piece* board[8][8]);
  // Printers (overrrides Piece):
  void printPiece1() override;
  void printPiece2() override;
  void printPiece3() override;
  void printPiece4() override;
  void printPiece5() override;
  // Destructor (overrides Piece):
  ~King() override {}
};
