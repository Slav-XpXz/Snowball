#pragma once
#include "bitboard.h"
#include "move.h"
#include <string>
#include <array>

enum Color : int {
	WHITE = 0,
	BLACK = 1,
	COLOR_NB = 2
};

enum Piece : int {
	NO_PIECE = -1,
	PAWN = 0,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
	PIECE_NB
};

enum Castling : int {
	WK = 1 << 0,
	WQ = 1 << 1,
	BK = 1 << 2,
	BQ = 1 << 3
};
struct Undo {
	Bitboard pieces[COLOR_NB][PIECE_NB];
	int castling_rights;
	int ep_square;
	int halfmove_clock;
};
struct Board {
	
	Bitboard pieces[COLOR_NB][PIECE_NB];

	Bitboard occ[COLOR_NB];
	Bitboard occ_all;

	Color side_to_move;
	int castling_rights;
	int ep_square;
	int halfmove_clock;
	int fullmove_number;

	Board() {
		clear();
	}

	void clear();
	void update_occupancy();
	bool set_fen(const std::string& fen);

	void make_move(Move m, Undo& u);
	void unmake_move(const Undo& u);


};