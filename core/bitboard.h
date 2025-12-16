#pragma once
#include <cstdint>
#include <intrin.h>
#include <bit>


enum Square : int {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    SQ_NONE
};

using Bitboard = uint64_t;

constexpr Bitboard BB(int sq) {
    return 1ULL << sq; 
}

constexpr Bitboard FILE_A = 0x0101010101010101ULL;
constexpr Bitboard FILE_H = FILE_A<<7;
constexpr Bitboard RANK_1 = 0xFFULL;
constexpr Bitboard RANK_2 = RANK_1 << 8;
constexpr Bitboard RANK_7 = RANK_1 << 48;
constexpr Bitboard RANK_8 = RANK_1 << 56;

inline int popcount(Bitboard b) {
    return std::popcount(b);
}

inline int lsb(Bitboard b) {
    unsigned long index;
    _BitScanForward64(&index, b);
    return static_cast<int>(index);
}

inline int msb(Bitboard b){
    unsigned long index;
    _BitScanReverse64(&index, b);
    return static_cast<int>(index);
}

inline int pop_lsb_sq(Bitboard& b) {
    int sq = std::countr_zero(b);
    b &= b - 1;
    return sq;
}
