#pragma once

int negamax(Board& b, int depth, int alpha, int beta);

Move find_best_move(Board& b, int depth);