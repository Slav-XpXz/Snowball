#pragma once
#include "board.h"
#include "move.h"
#include <vector>

void generate_pawn_moves(const Board& board, std::vector<Move>& moves);

void generate_king_moves(const Board& board, std::vector<Move>& moves);