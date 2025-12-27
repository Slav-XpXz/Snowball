#pragma once
#include "bitboard.h"


extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];

constexpr Bitboard FILE_B = FILE_A << 1;
constexpr Bitboard FILE_G = FILE_A << 6;

void init_leaper_attacks();
void print_bb(Bitboard b);
Bitboard bishop_attacks(int sq, Bitboard occ);