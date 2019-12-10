EXE = chess
SRC = $(wildcard *.cpp) #ChessMain.cpp ChessBoard.cpp Piece.cpp King.cpp Queen.cpp Bishop.cpp Rook.cpp Pawn.cpp
OBJ = $(SRC:%.cpp=%.o)
DEP = $(OBJ:%.o=%.d)
FLAGS = -Wall -g -MMD -c

$(EXE): $(OBJ)
	@echo 'Making chess...'
	@echo '           88                                          '
	@echo '           88                                          '
	@echo '           88                                          '
	@echo ' ,adPPYba, 88,dPPYba,   ,adPPYba, ,adPPYba, ,adPPYba,  '
	@echo 'a8"     "" 88P     "8a a8P_____88 I8[    "" I8[    ""  '
	@echo '8b         88       88 8PP"""""""  `"Y8ba,   `"Y8ba,   '
	@echo '"8a,   ,aa 88       88 "8b,   ,aa aa    ]8I aa    ]8I  '
	@echo ' `"Ybbd8"" 88       88  ""Ybbd8"" `"YbbdP"" `"YbbdP""  '


	g++ $^ -o $@

%.o: $.cpp
	g++ $(FLAGS) $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(EXE)

.PHONY: clean
