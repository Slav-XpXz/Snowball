#include "core/attacks.h"
#include "core/board.h"
#include <vector>
#include "core/move.h"
#include "core/movegen.h"
#include <iostream>

int main() {
    init_leaper_attacks();

    Board b;
    b.set_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<Move> moves;
    moves.clear();
    generate_pawn_moves(b, moves);

    std::cout << moves.size() << "\n";
    print_bb(knight_attacks[A1]);
    print_bb(knight_attacks[E4]); 
    print_bb(knight_attacks[H8]); 
}