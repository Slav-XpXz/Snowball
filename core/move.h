#pragma once
#include <cstdint>

using Move = uint32_t;


enum MoveFlags : uint32_t {
	QUIET = 0,
	CAPTURE = 1 << 16,
	DOUBLE_PUSH = 1 << 17,
	EN_PASSANT = 1 << 18,
	CASTLING = 1 << 19,
	PROMOTION = 1 << 20
};


inline Move make_move(int from, int to, uint32_t flags = QUIET, int promo = 0) {
	return (from) | (to << 6) | (promo << 12) | flags;
}

inline int move_from(Move m) {
	return m & 0x3f;
}
inline int move_to(Move m) {
	return (m >> 6) & 0x3f;
}
inline int move_promo(Move m) {
	return (m >> 12) & 0xf;
}
inline uint32_t move_flags(Move m) {
	return m & 0xFF0000;
}