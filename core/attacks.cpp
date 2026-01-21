#include "attacks.h"
#include "board.h"
#include <iostream>

Bitboard knight_attacks[64];
Bitboard king_attacks[64];

void init_leaper_attacks() {
    for (int sq = 0; sq < 64; sq++) {
        Bitboard b = BB(sq);


        Bitboard n = 0;


        n |= (b << 17) & ~FILE_A;
        n |= (b << 15) & ~FILE_H;
        n |= (b << 10) & ~(FILE_A | FILE_B);
        n |= (b << 6) & ~(FILE_G | FILE_H);


        n |= (b >> 17) & ~FILE_H;
        n |= (b >> 15) & ~FILE_A;
        n |= (b >> 10) & ~(FILE_G | FILE_H);
        n |= (b >> 6) & ~(FILE_A | FILE_B);

        knight_attacks[sq] = n;

        Bitboard k = 0;

        k |= (b << 8);
        k |= (b >> 8);
        k |= (b << 1) & ~FILE_A;
        k |= (b >> 1) & ~FILE_H;
        k |= (b << 9) & ~FILE_A;
        k |= (b << 7) & ~FILE_H;
        k |= (b >> 7) & ~FILE_A;
        k |= (b >> 9) & ~FILE_H;

        king_attacks[sq] = k;
    }
}



void print_bb(Bitboard b) {
    for (int r = 7; r >= 0; r--) {
        for (int f = 0; f < 8; f++) {
            int sq = r * 8 + f;
            std::cout << ((b & BB(sq)) ? "1 " : ". ");
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Bitboard bishop_attacks(int sq, Bitboard occ, Bitboard own_occ) {
    Bitboard attacks = 0;
    int r = sq / 8;
    int f = sq % 8;

    // Northeast
    for (int rr = r + 1, ff = f + 1; rr <= 7 && ff <= 7; rr++, ff++) {
        int s = rr * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // Northwest
    for (int rr = r + 1, ff = f - 1; rr <= 7 && ff >= 0; rr++, ff--) {
        int s = rr * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // Southeast
    for (int rr = r - 1, ff = f + 1; rr >= 0 && ff <= 7; rr--, ff++) {
        int s = rr * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // Southwest
    for (int rr = r - 1, ff = f - 1; rr >= 0 && ff >= 0; rr--, ff--) {
        int s = rr * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    return attacks;
}


Bitboard rook_attacks(int sq, Bitboard occ, Bitboard own_occ) {
    Bitboard attacks = 0;
    int r = sq / 8;
    int f = sq % 8;

    // North
    for (int rr = r + 1; rr <= 7; rr++) {
        int s = rr * 8 + f;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // South
    for (int rr = r - 1; rr >= 0; rr--) {
        int s = rr * 8 + f;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // East
    for (int ff = f + 1; ff <= 7; ff++) {
        int s = r * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    // West
    for (int ff = f - 1; ff >= 0; ff--) {
        int s = r * 8 + ff;
        if (own_occ & BB(s)) break;
        attacks |= BB(s);
        if (occ & BB(s)) break;
    }

    return attacks;
}

Bitboard queen_attacks(int sq, Bitboard occ, Bitboard own_occ) {
    return bishop_attacks(sq, occ, own_occ) | rook_attacks(sq, occ, own_occ);
}

inline int king_square(const Board& board, Color c) {
    return lsb_index(board.pieces[c][KING]);
}

bool is_square_attacked(const Board& board, int sq, Color by) {

    Bitboard target = BB(sq);

    if (by == WHITE) {
        if (((board.pieces[WHITE][PAWN] << 7) & ~FILE_H) & target) return true;
        if (((board.pieces[WHITE][PAWN] << 9) & ~FILE_A) & target) return true;
    }
    else {
        if (((board.pieces[BLACK][PAWN] >> 7) & ~FILE_A) & target) return true;
        if (((board.pieces[BLACK][PAWN] >> 9) & ~FILE_H) & target) return true;
    }

    Bitboard knights = board.pieces[by][KNIGHT];

    while(knights) {
		int from_sq = pop_lsb_sq(knights);
		if (knight_attacks[from_sq] & target) return true;
	}

    Bitboard diag = board.pieces[by][BISHOP] | board.pieces[by][QUEEN];
    while (diag) {
        int from_sq = pop_lsb_sq(diag);
        if (bishop_attacks(from_sq, board.occ_all, board.occ[by] & target)) return true;
    }

    Bitboard ortho = board.pieces[by][ROOK] | board.pieces[by][QUEEN];
    while (ortho) {
        int from_sq = pop_lsb_sq(ortho);
        if (rook_attacks(from_sq, board.occ_all, board.occ[by] & target)) return true;
    }

    Bitboard kings = board.pieces[by][KING];
    int king_sq = lsb_index(kings);
    if(king_attacks[king_sq] & target) return true;

    return false;
}