#pragma once
#include "board.h"
#include "move.h"
#include <vector>


void generate_moves(const Board& board, std::vector<Move>& moves);
void generate_pawn_moves(const Board& board, std::vector<Move>& moves);
void generate_king_moves(const Board& board, std::vector<Move>& moves);
void generate_knight_moves(const Board& board, std::vector<Move>& moves);
void generate_bishop_moves(const Board& board, std::vector<Move>& moves);
void generate_rook_moves(const Board& board, std::vector<Move>& moves);
void generate_queen_moves(const Board& board, std::vector<Move>& moves);