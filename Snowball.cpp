#include "core/attacks.h"
#include "core/board.h"
#include <vector>
#include "core/move.h"
#include "core/movegen.h"
#include "core/perft.h"
#include "search/search.h"
#include <iostream>

int main() {

    init_leaper_attacks();

    Board b;
    b.set_fen("startpos");

    Move best = find_best_move(b, 4);

    std::cout << "Best move: "
        << move_from(best) << " -> "
        << move_to(best) << "\n";

}