#include "movegen.h"
#include "bitboard.h"
#include "attacks.h"
#include <vector>

void generate_king_moves(const Board& board, std::vector<Move>& moves) {
	Color us = board.side_to_move;
	Color them = (us == WHITE) ? BLACK : WHITE;

	Bitboard king = board.pieces[us][KING];

	if (!king) return;

	int from = pop_lsb_sq(king);

	Bitboard attacks = king_attacks[from];
	Bitboard quiet = attacks & ~board.occ_all;
	Bitboard captures = attacks & board.occ[them];

	while (quiet) {
		int to = pop_lsb_sq(quiet);
		moves.push_back(make_move(from, to));
	}
	while (captures) {
		int to = pop_lsb_sq(captures);
		moves.push_back(make_move(from, to, CAPTURE));
	}

	if (us == WHITE) {
		if (board.castling_rights & WK) {
			if (!(board.occ_all & (BB(F1) | BB(G1)))) {
				moves.push_back(make_move(E1, G1, CASTLING));

			}
		}
		if (board.castling_rights & WQ) {
			if (!(board.occ_all & (BB(D1) | BB(C1) | BB(B1)))) {
				moves.push_back(make_move(E1, C1, CASTLING));
			}
		}
	}
	else {
		if (board.castling_rights & BK) {
			if (!(board.occ_all & (BB(F8) | BB(G8)))) {
				moves.push_back(make_move(E8, G8, CASTLING));
			}
		}
		if (board.castling_rights & BQ) {
			if (!(board.occ_all & (BB(D8) | BB(C8) | BB(B8)))) {
				moves.push_back(make_move(E8, C8, CASTLING));
			}
		}
	}
}

void generate_pawn_moves(const Board& board, std::vector<Move>& moves) {

	Color us = board.side_to_move;
	Color them = (us == WHITE) ? BLACK : WHITE;

	Bitboard pawns = board.pieces[us][PAWN];
	Bitboard empty = ~board.occ_all;

	if (us == WHITE) {

		Bitboard single = (pawns << 8) & empty;
		Bitboard promos = single & RANK_8;
		Bitboard quiet = single & ~RANK_8;

		while (quiet) {
			int to = pop_lsb_sq(quiet);
			moves.push_back(make_move(to - 8, to));
		}

		while (promos) {
			int to = pop_lsb_sq(promos);
			int from = to - 8;
			moves.push_back(make_move(from, to, PROMOTION, QUEEN));
			moves.push_back(make_move(from, to, PROMOTION, ROOK));
			moves.push_back(make_move(from, to, PROMOTION, BISHOP));
			moves.push_back(make_move(from, to, PROMOTION, KNIGHT));
		}

		Bitboard dbl = ((pawns & RANK_2) << 8) & empty;
		dbl = (dbl << 8) & empty;

		while (dbl) {
			int to = pop_lsb_sq(dbl);
			moves.push_back(make_move(to - 16, to, DOUBLE_PUSH));
		}

		Bitboard left = (pawns << 7) & board.occ[them] & ~FILE_H;
		Bitboard right = (pawns << 9) & board.occ[them] & ~FILE_A;

		while (left) {
			int to = pop_lsb_sq(left);
			moves.push_back(make_move(to - 7, to, CAPTURE));
		}

		while (right) {
			int to = pop_lsb_sq(right);
			moves.push_back(make_move(to - 9, to, CAPTURE));
		}

		if (board.ep_square != -1) {
			Bitboard ep = BB(board.ep_square);
			if ((pawns << 7) & ep & ~FILE_H) {
				moves.push_back(make_move(board.ep_square - 7, board.ep_square, EN_PASSANT));
			}
			if ((pawns << 9) & ep & ~FILE_A) {
				moves.push_back(make_move(board.ep_square - 9, board.ep_square, EN_PASSANT));
			}
		}
		else {

			Bitboard single = (pawns >> 8) & empty;
			Bitboard promos = single & RANK_1;
			Bitboard quiet = single & ~RANK_1;

			while (quiet) {
				int to = pop_lsb_sq(quiet);
				moves.push_back(make_move(to + 8, to));
			}

			while (promos) {
				int to = pop_lsb_sq(promos);
				int from = to + 8;
				moves.push_back(make_move(from, to, PROMOTION, QUEEN));
				moves.push_back(make_move(from, to, PROMOTION, ROOK));
				moves.push_back(make_move(from, to, PROMOTION, BISHOP));
				moves.push_back(make_move(from, to, PROMOTION, KNIGHT));
			}
			Bitboard dbl = ((pawns & RANK_7) >> 8) & empty;
			dbl = (dbl >> 8) & empty;

			while (dbl) {
				int to = pop_lsb_sq(dbl);
				moves.push_back(make_move(to + 16, to, DOUBLE_PUSH));
			}

			Bitboard left = (pawns >> 9) & board.occ[them] & ~FILE_H;
			Bitboard right = (pawns >> 7) & board.occ[them] & ~FILE_A;

			while (left) {
				int to = pop_lsb_sq(left);
				moves.push_back(make_move(to + 9, to, CAPTURE));
			}
			while (right)
			{
				int to = pop_lsb_sq(right);
				moves.push_back(make_move(to + 7, to, CAPTURE));
			}

			if (board.ep_square != -1) {
				Bitboard ep = BB(board.ep_square);
				if ((pawns >> 9) & ep & ~FILE_H) {
					moves.push_back(make_move(board.ep_square + 9, board.ep_square, EN_PASSANT));
				}
				if((pawns >> 7) & ep & ~FILE_A) {
					moves.push_back(make_move(board.ep_square + 7, board.ep_square, EN_PASSANT));
				}
			}


		}
	}
}