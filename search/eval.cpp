#include "C:\Users\MainUser\Documents\Snowball\Snowball\Snowball\core\board.h"
#include "eval.h"

int piece_values[PIECE_NB] = {
	100, // pawn
	320, // knight
	330, // bishop
	500, // rook
	900, // queen
	0 // king
};

int evaluate(const Board& b) {
	int score = 0;

	for (int p = 0; p < PIECE_NB; p++) {
		score += piece_values[p] * popcount(b.pieces[WHITE][p]);
		score += piece_values[p] * popcount(b.pieces[BLACK][p]);
	}
	return (b.side_to_move == WHITE) ? score : -score;
}