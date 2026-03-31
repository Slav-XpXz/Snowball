#include <string>
#include <vector>
#include <board.h>
#include <move.h>
#include <movegen.h>
#include "search.h"
#include "eval.h"
#include <attacks.h>


int nodes = 0;

int negamax(Board& b, int depth, int alpha, int beta) {

	if (depth == 0)
	{
		return evaluate(b);
	}
	nodes++;

	std::vector<Move> moves;
	generate_moves(b, moves);

	Color us = b.side_to_move;
	Color them = (us == WHITE) ? BLACK : WHITE;

	int legal_moves = 0;

	for (Move m : moves) {
		Undo u;
		b.make_move(m, u);
		int ksq = king_square(b, us);

		if (!is_square_attacked(b, ksq, them)) {
			legal_moves++;

			int score = -negamax(b, depth - 1, -beta, -alpha);

			b.unmake_move(u);

			if (score >= beta)
				return beta;
			if (score > alpha)
				alpha = score;
		}
		else {
			b.unmake_move(u);
		}
	}

	if (legal_moves == 0) {
		int ksq = king_square(b, us);

		if (is_square_attacked(b, ksq, them))
			return -100000 + (5 - depth); //checkmate
		else
			return 0; //stalemate
	}
	
	return alpha;
}

Move find_best_move(Board& b, int depth) {
	
	std::vector<Move> moves;
	generate_moves(b, moves);

	Move best_move = 0;
	int best_score = -1000000;

	Color us = b.side_to_move;
	Color them = (us == WHITE) ? BLACK : WHITE;

	for (Move m : moves) {
		Undo u;
		b.make_move(m, u);

		int ksq = king_square(b, us);

		if (!is_square_attacked(b, ksq, them)) {

			int score = -negamax(b, depth - 1, -1000000, 1000000);

			if (score > best_score) {
				best_score = score;
				best_move = m;
			}
		}
		b.unmake_move(u);
	}
	return best_move;
}