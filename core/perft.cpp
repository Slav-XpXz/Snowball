#include "perft.h"
#include "movegen.h"
#include "attacks.h"


uint64_t perft(Board& b, int depth) {

    if (depth == 0)
        return 1;

    std::vector<Move> moves;
    generate_moves(b, moves);

    uint64_t nodes = 0;
    Color us = b.side_to_move;

    for (Move m : moves) {
        Undo u;
        b.make_move(m, u);

        int ksq = king_square(b, us);
        if (!is_square_attacked(b, ksq,
            (us == WHITE) ? BLACK : WHITE)) {

            nodes += perft(b, depth - 1);
        }

        b.unmake_move(u);
    }

    return nodes;
}