#include "board.h"
#include <assert.h>
#include <sstream>
#include <cstring>
#include <cctype>

void Board::clear() {
	std::memset(pieces, 0, sizeof(pieces));
	occ[WHITE] = occ[BLACK] = occ_all = 0;
	side_to_move = WHITE;
	castling_rights = 0;
	ep_square = -1;
	halfmove_clock = 0;
	fullmove_number = 1;
}

void Board::update_occupancy() {
	occ[WHITE] = occ[BLACK] = 0;
	for (int c = 0; c < COLOR_NB; c++) {
		for (int p = 0; p < PIECE_NB; p++) {
			occ[c] |= pieces[c][p];
		}
	}
	occ_all = occ[WHITE] | occ[BLACK];
} 

bool Board::set_fen(const std::string& fen) {
	clear();

	std::istringstream iss(fen);
	std::string board_part, stm, castling, ep;

	iss >> board_part >> stm >> castling >> ep >> halfmove_clock >> fullmove_number;

	int sq =  56;

	for (char c : board_part) {
		if (c == '/') {
			sq -= 16;
		}
		else if (c >= '1' && c <= '8') {
			sq += c - '0';
		}
		else {
			Color col = isupper(c) ? WHITE : BLACK;
			char pc = tolower(c);

			Piece piece;
			switch (pc) {
			case 'p': piece = PAWN; break;
			case 'n': piece = KNIGHT; break;
			case 'b': piece = BISHOP; break;
			case 'r': piece = ROOK; break;
			case 'q': piece = QUEEN; break;
			case 'k': piece = KING; break;
			default: return false;
			}

			pieces[col][piece] |= BB(sq);
			sq++;
		}
	}

	side_to_move = (stm == "w") ? WHITE : BLACK;

	castling_rights = 0;
	if (castling.find('K') != std::string::npos) castling_rights |= WK;
	if (castling.find('Q') != std::string::npos) castling_rights |= WQ;
	if (castling.find('k') != std::string::npos) castling_rights |= BK;
	if (castling.find('q') != std::string::npos) castling_rights |= BQ;

	if (ep != "-") {
		int file = ep[0] - 'a';
		int rank = ep[1] - '1';
		ep_square = rank * 8 + file;
	}
	else {
		ep_square = -1;
	}
	update_occupancy();
	return true;
}

void Board::make_move(Move m, Undo& u) {
	std::memcpy(u.pieces, pieces, sizeof(pieces));
	u.castling_rights = castling_rights;
	u.ep_square = ep_square;
	u.halfmove_clock = halfmove_clock;

	int from = move_from(m);
	int to = move_to(m);
	uint32_t flags = move_flags(m);

	Color us = side_to_move;
	Color them = (us == WHITE) ? BLACK : WHITE;


	Piece moving = NO_PIECE;
	for (int p = 0; p < PIECE_NB; p++) {
		if (pieces[us][p] & BB(from)) {
			moving = (Piece)p;
			break;
		}
	}


	assert(moving != NO_PIECE);


	pieces[us][moving] &= ~BB(from);


	if (flags & CAPTURE) {
		for (int p = 0; p < PIECE_NB; p++) {
			pieces[them][p] &= ~BB(to);
		}
	}

	pieces[us][moving] |= BB(to);


	ep_square = -1;
	if (moving == PAWN && (flags & DOUBLE_PUSH)) {
		ep_square = (us == WHITE) ? to - 8 : to + 8;
	}

	side_to_move = them;
	update_occupancy();
}

void Board::unmake_move(const Undo& u) {
	std::memcpy(pieces, u.pieces, sizeof(pieces));
	castling_rights = u.castling_rights;
	ep_square = u.ep_square;
	halfmove_clock = u.halfmove_clock;

	side_to_move = (side_to_move == WHITE) ? BLACK : WHITE;
	update_occupancy();
}