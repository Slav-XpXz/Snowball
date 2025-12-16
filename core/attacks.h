#pragma once
#include "bitboard.h"


extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];


void init_leaper_attacks();


void print_bb(Bitboard b);