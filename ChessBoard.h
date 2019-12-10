// Include other header files:
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"

class ChessBoard {
 private:
  // Variables:
  Piece* whiteArray[16];
  Piece* blackArray[16];
  Piece* board[8][8];
  bool is_white_turn = true;
  bool is_game_over = false;
  bool in_check = false;
  /* --- Private Functions --- */
  // Setup Functions:
  void setTeam(bool is_white, Piece* team_array[]);
  void setBoard();
  // Input Functions
  int  getStringLength(char const* input);
  bool isCorrectMove(char const from[], char const to[], int* const inputs);
  // Move Functions:
  Piece* makeMove(int const inputs[4], bool not_peek);  
  void undoMove(int const inputs[4], Piece *killed_piece, bool not_peek);
  // Game Status Functions:
  bool isCheck(bool white_team);
  bool isCheckMate(bool white_team);
  bool isStaleMate(bool white_team);
  bool isCastling(bool white_team, int const inputs[4]);
  bool canCastle(bool white_team, int const inputs[4]);
  bool underThreat(bool white_turn, int const check_rol, int const check_col);
  // Printing Related Functions:
  void printBoard();
  void printRow(int rownum);
 public:
  ChessBoard();
  void submitMove(char const from[], char const to[]);
  void resetBoard();
  ~ChessBoard();
};
