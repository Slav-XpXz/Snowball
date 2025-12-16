#include "attacks.h"
#include <iostream>

Bitboard knight_attacks[64];
Bitboard king_attacks[64];

void init_leaper_attacks() {
    for (int sq = 0; sq < 64; sq++) {
        Bitboard b = BB(sq);

        Bitboard n = 0;
        n |= (b << 17) & ~FILE_A;
        n |= (b << 15) & ~FILE_H;
        n |= (b << 10) & ~(FILE_A | (FILE_A << 1));
        n |= (b << 6)  & ~(FILE_H | (FILE_H >> 1));
        n |= (b >> 17) & ~FILE_H;
        n |= (b >> 15) & ~FILE_A;
        n |= (b >> 10) & ~(FILE_H | (FILE_H >> 1));
        n |= (b >> 6)  & ~(FILE_A | (FILE_A << 1));
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