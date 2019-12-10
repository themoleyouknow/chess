#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

class Piece {
  friend class ChessBoard;
 protected:
  // Class members:
  bool is_white;
  bool is_dead = false;
  bool has_moved = false;
  int row, col;
  std::string name;
  // Setters:
  void  movePiece(int to_row, int to_col, bool not_peek) {
    row = to_row; col = to_col;
    if (!has_moved && not_peek) {has_moved = true;}
  }
  void  toggleIsDead()          {is_dead = !is_dead;}
 public:
  // Constructor:
  Piece(std::string name, bool is_white, int row, int col) : name(name), is_white(is_white), row(row), col(col) {}
  // Getters:
  bool  getIsWhite() const      {return is_white;}
  bool  getIsDead() const       {return is_dead;}
  bool  getHasMoved() const     {return has_moved;}
  int   getRow() const          {return row;}
  int   getCol() const          {return col;}
  std::string  getName() const  {return name;}
  // Move Validators:
  bool  isValidMove(int to_row, int to_col, Piece* board[8][8]);
  bool  isLegal(int to_row, int to_col, Piece *board[8][8]);
  bool  canMove(Piece *board[8][8]);
  virtual bool canSee(int row, int col, Piece* board[8][8]) = 0;
  // Printers:
  virtual void printPiece1() = 0;
  virtual void printPiece2() = 0;
  virtual void printPiece3() = 0;
  virtual void printPiece4() = 0;
  virtual void printPiece5() = 0;
  // Destructor:
  virtual ~Piece() {}
};
#endif
