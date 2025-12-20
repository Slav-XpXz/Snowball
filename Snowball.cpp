#include "core/attacks.h"
#include "core/board.h"
#include <vector>
#include "core/move.h"
#include "core/movegen.h"
#include <iostream>

int main() {

    std::vector<Move> moves;
    init_leaper_attacks();

    Board b;
    b.set_fen("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
    moves.clear();
    generate_king_moves(b, moves);

    print_bb(king_attacks[E1]);
}