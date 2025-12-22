#include "perft.h"
#include "movegen.h"

uint64_t perft(Board& b, int depth) {
    if (depth == 0)
        return 1;

    std::vector<Move> moves;
    generate_moves(b, moves);

    uint64_t nodes = 0;
    for (auto m : moves) {
        Undo u;
        b.make_move(m, u);
        nodes += perft(b, depth - 1);
        b.unmake_move(u);
    }
    return nodes;
}