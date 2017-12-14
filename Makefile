CC=g++

CFLAGS=-c -Wall
all:  execute

execute: main.o Game.o Bishop.o Pawn.o King.o Rook.o Board.o Piece.o Player.o
	$(CC) main.o Game.o Bishop.o Pawn.o King.o Rook.o Board.o Piece.o Player.o -o execute

main.o: main.cpp Game.cpp
	$(CC) $(CFLAGS) main.cpp

Game.o: Game.cpp Game.hpp Board.cpp Board.hpp Player.cpp Player.hpp
	$(CC) $(CFLAGS) Game.cpp

Board.o: Board.cpp Board.hpp Bishop.cpp Bishop.hpp Pawn.cpp Pawn.hpp King.cpp King.hpp Rook.cpp Rook.hpp Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) Board.cpp 

Bishop.o: Bishop.cpp Bishop.hpp Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) Bishop.cpp 

Pawn.o: Pawn.cpp Pawn.hpp Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) Pawn.cpp 

King.o: King.cpp King.hpp Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) King.cpp 

Rook.o: Rook.cpp Rook.hpp Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) Rook.cpp 

Piece.o: Piece.cpp Piece.hpp
	$(CC) $(CFLAGS) Piece.cpp

Player.o: Player.cpp Player.hpp
	$(CC) $(CFLAGS) Player.cpp

clean:
	rm -rf *o execute
