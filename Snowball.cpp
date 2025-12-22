#include "core/attacks.h"
#include "core/board.h"
#include <vector>
#include "core/move.h"
#include "core/movegen.h"
#include "core/perft.h"
#include <iostream>

int main() {

    std::vector<Move> moves;
    init_leaper_attacks();

    Board b;
    b.set_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << perft(b, 1) << "\n";
    std::cout << perft(b, 2) << "\n";
    std::cout << perft(b, 3) << "\n";
}