#pragma once
#include "bitboard.h"


extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];

constexpr Bitboard FILE_B = FILE_A << 1;
constexpr Bitboard FILE_G = FILE_A << 6;

void init_leaper_attacks();
void print_bb(Bitboard b);
Bitboard bishop_attacks(int sq, Bitboard occ, Bitboard own_occ);
Bitboard rook_attacks(int sq, Bitboard occ, Bitboard own_occ);
Bitboard queen_attacks(int sq, Bitboard occ, Bitboard own_occ);
bool is_square_attacked(const Board& board, int sq, Color by);