#include "ChessBoard.h"
/* -------------------- Constructor -------------------- */
ChessBoard::ChessBoard() {
  std::cout << "A new chess game is started!" << std::endl;
  // Set up whiteArray and blackArray using private functions setTeam::
  setTeam(true, whiteArray);
  setTeam(false, blackArray);
  // Set board:
  setBoard();
  // Print board:
  //printBoard();
}
/* -------------------- Setup Functions -------------------- */
void ChessBoard::setTeam(bool is_white, Piece* team_array[]) {
  // Declare variables:
  int base_row, pawn_row;
  // Assign setting variables:
  if (is_white) {base_row = 7; pawn_row = 6;}
  else {base_row = 0; pawn_row = 1;}
  // Create Team:
  for (int col_count = 0; col_count < 16; ++col_count) {
    switch(col_count) {
    case 0 : team_array[col_count] = new Rook("Rook", is_white, base_row, col_count); break;
    case 1 : team_array[col_count] = new Knight("Knight", is_white, base_row, col_count); break;
    case 2 : team_array[col_count] = new Bishop("Bishop", is_white, base_row, col_count); break;
    case 3 : team_array[col_count] = new Queen("Queen", is_white, base_row, col_count); break;
    case 4 : team_array[col_count] = new King("King", is_white, base_row, col_count); break;
    case 5 : team_array[col_count] = new Bishop("Bishop", is_white, base_row, col_count); break;
    case 6 : team_array[col_count] = new Knight("Knight", is_white, base_row, col_count); break;
    case 7 : team_array[col_count] = new Rook("Rook", is_white, base_row, col_count); break;
    default : team_array[col_count] = new Pawn("Pawn", is_white, pawn_row,col_count-8); break;
    }
  }
}
void ChessBoard::setBoard() {
  // Iterate across 2D board array to assign correct pointers:
  // for loop to iterate across rows:
  for (int count1 = 0; count1 < 8; ++count1) {
    // for loop to iterate across columns:
    for (int count2 = 0; count2 < 8; ++count2) {
      // Check if we're on first or last rows
      if (count1 == 0 || count1 == 7){
	if (!count1) {board[count1][count2] = blackArray[count2];}
	else {board[count1][count2] = whiteArray[count2];}
      // Check if we're on second or penultimate row:
      }else if (count1 == 1 || count1 == 6) {
	if (!(count1-1)) {board[count1][count2] = blackArray[count2 + 8];}
	else {board[count1][count2] = whiteArray[count2 + 8];}
      // Set nullptrs everywhere else:
      }else {
	board[count1][count2] = nullptr;
      }
    }
  }
}
void ChessBoard::resetBoard() {
  // for loop to iterate across rows:
  for (int row_count = 0; row_count < 16; ++row_count) {
    // Take opportunity to delete the old pieces:
    delete whiteArray[row_count]; whiteArray[row_count] = nullptr;
    delete blackArray[row_count]; blackArray[row_count] = nullptr;
  }
  // Set up teams again:
  setTeam(true, whiteArray);
  setTeam(false, blackArray);
  // Set board:
  setBoard();
  // Reset board toggles:
  if (!is_white_turn) {is_white_turn = true;}
  if (is_game_over) {is_game_over = false;}
  if (in_check) {in_check = false;}
  // Print message:
  std::cout << "A new chess game is started!" << std::endl;
  //printBoard();
}
/* -------------------- Input functions -------------------- */
void ChessBoard::submitMove(char const from[], char const to[]) {
  /* ----- Check and process inputs ----- */

  // Check if game is over:
  if (is_game_over) {
    std::cerr << "The game is over, I'm not taking any more moves!" << std::endl;
    return;
  }
  // Check if input is of correct size:
  if (getStringLength(from) != 2 || getStringLength(to) != 2) {
    std::cerr << "Invalid Input Error: Input strings are of incorrect length." << std::endl;
    return;
  }
  // Check if input is a correct move for a board::
  int inputs[4];
  if (!isCorrectMove(from, to, inputs)) {
    std::cerr << "Invalid Input Error: Incorrect inputs supplied for a move from " << from;
    std:: cerr << " to " << to << "!" << std::endl;
    return;
  }
  // Check if the move is to the same place:
  if (inputs[0] == inputs[2] && inputs[1] == inputs[3]) {
    std::cerr << "Invalid Move Error: Inputs are the same!" << std::endl;
    return;
  }
  // Check there is an actual piece to be moved:
  if(board[inputs[0]][inputs[1]] == nullptr) {
    std::cerr << "There's no piece at position " << from << "!" << std::endl;
    return;
  }
  // Check that it's this piece's team's turn to move:
  if(board[inputs[0]][inputs[1]]->getIsWhite()^(is_white_turn)) {
    std::cerr << "It's not " << (is_white_turn ? "Black's" : "White's");
    std::cerr << " turn to move!" << std::endl;
    return;
  }
  // Check that this is a valid move for this piece:
  if ( !(board[inputs[0]][inputs[1]]->isValidMove(inputs[2], inputs[3], board)) ) {
    std::cerr << (is_white_turn ? "White's " : "Black's ");
    std::cerr << board[inputs[0]][inputs[1]]->getName();
    std::cerr << " cannot move from " << from << " to " << to << std::endl;
    return;
  }
  
  /* ----- Attempt to execute the move ----- */

  // Peek the move, and afterwards check that we aren't putting outselves in check:
  Piece* move_return = makeMove(inputs, false);
  if (isCheck(is_white_turn)) {
    undoMove(inputs, move_return, false);
    std::cerr << "Invalid Move Error: " << (is_white_turn ? "White" : "Black");
    std::cerr << " is still in check!" << std::endl;
    return;
  }
  // Undo peek:
  undoMove(inputs, move_return, false);
  // Execute the move, checking also whether this is castling:
  if (isCastling(is_white_turn, inputs)) {
    int rook_inputs[4];
    rook_inputs[0] = inputs[0];
    rook_inputs[2] = inputs[0];
    if (inputs[3]-inputs[1] > 0) {
      rook_inputs[1] = 7;
      rook_inputs[3] = 5;
    }else {
      rook_inputs[1] = 0;
      rook_inputs[3] = 3;
    }
    std::cout << "Castling: ";
    makeMove(rook_inputs, true);
  }
  std::cout << (is_white_turn ? "White's " : "Black's ");
  std::cout << board[inputs[0]][inputs[1]]->getName() << " moves from ";
  std::cout << from << " to " << to;
  move_return = makeMove(inputs, true);
  // Change the team turn:
  is_white_turn = !is_white_turn;
  std::cout << std::endl;
  // Print the board after the move:
  //printBoard();
  
  /* ----- Check the game status ----- */

  // Toggle in_check value if was true, as this team can no longer be in check:
  if (in_check) {in_check = false;}
  // Check if other team is in check, and if so, in checkmate:
  if (isCheck(is_white_turn)) {
    // Toggle in_check value::
    in_check = true;
    std::cout << (is_white_turn ? "White" : "Black");
    // Check for checkmate:
    if (isCheckMate(is_white_turn)) {
      std::cout << " is in checkmate";
      is_game_over = true;
      return;
    }else {
      std::cout << " is in check" << std::endl;
      return;
    }
  }
  // Check opposing team for Stalemate:
  if (isStaleMate(is_white_turn)) {
    std::cout << (is_white_turn ? "White" : "Black");
    std::cout << " is in stalemate" << std::endl;
    is_game_over = true;
    return;
  }
}

bool ChessBoard::isCorrectMove(char const from[], char const to[], int* const inputs) {
  // Return the input data as integers to inputs in format ( from_row, from_col, to_row, to_col );
  if ((*(inputs    ) = 7 - int(from[1] - '1')) < 0 || *(inputs) > 7 ) {return false;}
  if ((*(inputs + 1) = int(from[0] - 'A')) < 0 || *(inputs + 1) > 7 ) {return false;}
  if ((*(inputs + 2) = 7 - int(to[1] - '1')) < 0 || *(inputs + 2) > 7 ) {return false;}
  if ((*(inputs + 3) = int(to[0] - 'A')) < 0 || *(inputs + 3) > 7 ) {return false;}
  return true;
}

int ChessBoard::getStringLength(char const* input) {
  int count = 0;
  while (*(input + count) != '\0') {
    ++count;
  }
  return count;
}

/* -------------------- Move Functions -------------------- */
Piece* ChessBoard::makeMove(int const inputs[4], bool not_peek) {
  Piece* killed_piece = nullptr;
  // Check if we're going to be killing something:
  if (board[inputs[2]][inputs[3]] != nullptr) {
    // Toggle piece's is_dead:
    board[inputs[2]][inputs[3]]->toggleIsDead();
    // Set killed_piece to point to the killed piece:
    killed_piece = board[inputs[2]][inputs[3]];
    // Print the kill message if we're not peeking this move:
    if (not_peek) {
      std::cout << " taking " << (is_white_turn ? "Black's " : "White's ");
      std::cout << killed_piece->getName();
    }
  }
  // Replace destination pointer with source pointer:
  board[inputs[2]][inputs[3]] = board[inputs[0]][inputs[1]];
  // Replace source pointer with nullptr:
  board[inputs[0]][inputs[1]] = nullptr;
  // Update piece's coordinates:
  board[inputs[2]][inputs[3]]->movePiece(inputs[2], inputs[3], not_peek);
  // Return the killed_piece pointer:
  return killed_piece;
}

void ChessBoard::undoMove(int const inputs[4], Piece *killed_piece, bool not_peek) {
  // Set source to destination piece:
  board[inputs[0]][inputs[1]] = board[inputs[2]][inputs[3]];
  // Check if we've killed a piece and toggle is_dead:
  if (killed_piece != nullptr) {killed_piece->toggleIsDead();}
  // Replace destination with killed_piece pointer:
  board[inputs[2]][inputs[3]] = killed_piece;
  board[inputs[0]][inputs[1]]->movePiece(inputs[0], inputs[1], not_peek);
}

bool ChessBoard::isCastling(bool white_team, int const inputs[4]) {
  if ( (inputs[0] == 7 || inputs[0] == 0) && inputs[1] == 4 &&
       !(board[inputs[0]][inputs[1]]->getHasMoved())        ) {
    // Return true!
    return true;
  }
  // Return false!
  return false;
}

/* --------------------  Game Status Functions -------------------- */
bool ChessBoard::isCheck(bool white_team) {
  // Declare and initialise team arrays:
  Piece *this_team_king = (white_team ? whiteArray[4] : blackArray[4]);
  int king_row = this_team_king->getRow();
  int king_col = this_team_king->getCol();
  Piece **that_team_array = (white_team ? blackArray : whiteArray);
  // Loop through opposing team pieces:
  for (int array_count = 0; array_count < 16; ++array_count) {
    if (!(that_team_array[array_count]->getIsDead()) &&
	that_team_array[array_count]->isValidMove(king_row, king_col, board)) {
      // Return true!
      return true;
    }
  }
  return false;
}

bool ChessBoard::isCheckMate(bool white_team_turn) {
  // Check if opposing team in check:
  if (!in_check) {return false;}
  // Declare variables:
  int inputs[4];
  Piece* move_return;
  // Declare and initialise opposing team array pointer:
  Piece **this_team_array = (white_team_turn ? whiteArray : blackArray);  
  // Loop through opposing team pieces:
  for (int array_count = 0; array_count < 16; ++array_count) {
    // Loop through rows:
    for (int row_count = 0; row_count < 16; ++row_count) {
      // Loop through columns:
      for (int col_count = 0; col_count < 16; ++col_count) {
	// Check if this is a valid move for this piece:
	if (!(this_team_array[array_count]->getIsDead()) &&
	    (this_team_array[array_count]->isValidMove(row_count, col_count, board))) {
	  // Update inputs array to submit to makeMove:
	  inputs[0] = this_team_array[array_count]->getRow();
	  inputs[1] = this_team_array[array_count]->getCol();
	  inputs[2] = row_count;
	  inputs[3] = col_count;
	  // Peek move for this piece:
	  move_return = makeMove(inputs, false);
	  // Check if opposing team still in check:
	  if (isCheck(white_team_turn)) {
	    // Undo move and keep trying:
	    undoMove(inputs, move_return, false);
	  }else {
	    // We've found a valid move! Undo and return false:
	    undoMove(inputs, move_return, false);
	    return false;
	  }
	}
      }
    }
  }
  // Checkmate! Set game_over to true:
  is_game_over = true;
  // Return true!
  return true;
}

bool ChessBoard::isStaleMate(bool white_team_turn) {
  // Check if opposing team in check:
  if (in_check) {return false;}
  // Declare and initialise opposing team array pointer:
  Piece **this_team_array = (white_team_turn ? whiteArray : blackArray);
  Piece *move_return = nullptr;
  int inputs[4];
  // Loop through opposing team pieces:
  for (int array_count = 0; array_count < 16; ++array_count) {
    // Loop through rows:
    for (int row_count = 0; row_count < 16; ++row_count) {
      // Loop through columns:
      for (int col_count = 0; col_count < 16; ++col_count) {
	// Check if this is a valid move for this piece:
	if (!(this_team_array[array_count]->getIsDead()) &&
	    this_team_array[array_count]->isValidMove(row_count, col_count, board)) {
	  inputs[0] = this_team_array[array_count]->getRow();
	  inputs[1] = this_team_array[array_count]->getCol();
	  inputs[2] = row_count;
	  inputs[3] = col_count;
	  // Peek move for this piece:
	  move_return = makeMove(inputs, false);
	  // Check if opposing team still in check:
	  if (isCheck(white_team_turn)) {
	    // Undo move and keep trying:
	    undoMove(inputs, move_return, false);
	  }else {
	    // We've found a valid move! Undo and return false:
	    undoMove(inputs, move_return, false);
	    return false;
	  }
	}
      }
    }
  }
  // Stalemate! Set game_over to true:
  is_game_over = true;
  // Return true!
  return true;
}

// NB This function not needed! (But who knows, was fun to thinkn about)
bool ChessBoard::canCastle(bool white_team, int const inputs[4]) {
  // Check that if this is a white team turn, that source is the white king spot
  // || that if this is a black team turn, that source is the black king spot
  // && that the piece hasn't moved, && that it won't be moving up or down.
  if ((( white_team && inputs[0] == 0 && inputs[1] == 4)  ||
       (!white_team && inputs[0] == 7 && inputs[1] == 4)) &&
      !board[inputs[0]][inputs[1]]->getHasMoved()         &&
      inputs[3]-inputs[1] == 0                            ){
    // Check if we're moving right by 2, and that the
    // corresponding rook spot isn't empty and hasn't moved:
    if (inputs[2]-inputs[0] == 2         &&
	board[inputs[0]][7] != nullptr   &&
	!board[inputs[0]][7]->getHasMoved()) {
      // Check that the path is clear, and that the king
      // isn't passing through any threatened spaces:
      if (board[inputs[0]][5] == nullptr &&
	  board[inputs[0]][6] == nullptr &&
	  !underThreat(white_team, inputs[0], 5) &&
	  !underThreat(white_team, inputs[0], 6)  ) {
	// Return true!
	return true;
      }
    // Check if we're moving left by 2, and that the
    // corresponding rook spot isn't empty and hasn't moved:  
    }else if (inputs[2]-inputs[0] == -2        &&
	      board[inputs[0]][0] != nullptr   &&
	      !board[inputs[0]][0]->getHasMoved()){
      // Check that the path is clear, and that the king
      // isn't passing through any threatened spaces:
      if (board[inputs[0]][3] == nullptr &&
	  board[inputs[0]][2] == nullptr &&
	  board[inputs[0]][1] == nullptr &&	  
	  !underThreat(white_team, inputs[0], 3) &&
	  !underThreat(white_team, inputs[0], 2)  ) {
	// Return true!
	return true;
      }
    }
  }
  // Return false!
  return false;
}
// NB This function not needed! (But who knows, was fun to think about)
bool ChessBoard::underThreat(bool white_turn, int const check_row, int const check_col) {
  Piece **that_team_array = (white_turn ? blackArray : whiteArray);
  for (int array_count = 0; array_count < 16 ; ++array_count) {
    if (!(that_team_array[array_count]->getIsDead()) &&
	that_team_array[array_count]->isValidMove(check_row, check_col, board)) {
      return true;
    }
  }
  return false;
}

/* -------------------- Printing Functions -------------------- */
void ChessBoard::printBoard() {
  // Print top:
  std::cout << "       A         B         C         D         E         F         G         H       " << std::endl;
  std::cout << "  =================================================================================  " << std::endl;
  for (int count = 0; count < 8; count++) {
    printRow(count);
  }
  std::cout << "       A         B         C         D         E         F         G         H       " << std::endl;
}

void ChessBoard::printRow(int rownum) {  
  for (int count1 = 0; count1 < 5; count1++) {
    std::cout << ((count1 == 2) ? char (56-rownum) : ' '); 
    std::cout << " |";
    for (int count2 = 0; count2 < 8; count2++) {
      std::cout << "|  ";
      if (count2 != 0) {std::cout << ' ';}
      if (board[rownum][count2] != nullptr) {
	switch(count1) {
	case 0 : board[rownum][count2]->printPiece1();break;
	case 1 : board[rownum][count2]->printPiece2();break;
	case 2 : board[rownum][count2]->printPiece3();break;
	case 3 : board[rownum][count2]->printPiece4();break;
	case 4 : board[rownum][count2]->printPiece5();break;
	}
      }else {std::cout << "   ";}
      if (count2 != 7) {std::cout << "   ";}
      else {std::cout << "  ";}
    }
    std::cout << "|| ";
    std::cout << ((count1 == 2) ? char (56-rownum) : ' ') << std::endl;
  }
  std::cout << "  =================================================================================  " << std::endl;
}

/* -------------------- Destructor -------------------- */
ChessBoard::~ChessBoard() {
  for (int count = 0; count < 16; count++) {
    delete whiteArray[count];
    delete blackArray[count];
  }
}

