#include "board.h"
#include "maps.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void board_load(Game* game) {
    assert(game != NULL);
    
    game->rows = MAP_ROWS;
    game->cols = MAP_COLS;
    
    // Copy static map to game board
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            game->board[r][c] = STATIC_MAP[r][c];
        }
    }
    
    // Count initial pellets
    game->pelletsRemaining = board_count_pellets(game);
}

bool board_is_valid_pos(const Game* game, Pos pos) {
    assert(game != NULL);
    
    return pos.r >= 0 && pos.r < game->rows &&
           pos.c >= 0 && pos.c < game->cols &&
           !board_is_wall(game, pos);
}

bool board_is_wall(const Game* game, Pos pos) {
    assert(game != NULL);
    
    if (pos.r < 0 || pos.r >= game->rows || pos.c < 0 || pos.c >= game->cols) {
        return true; // Out of bounds counts as wall
    }
    
    return game->board[pos.r][pos.c] == '#';
}

bool board_has_pellet(const Game* game, Pos pos) {
    assert(game != NULL);
    
    if (pos.r < 0 || pos.r >= game->rows || pos.c < 0 || pos.c >= game->cols) {
        return false;
    }
    
    return game->board[pos.r][pos.c] == '.';
}

void board_remove_pellet(Game* game, Pos pos) {
    assert(game != NULL);
    assert(board_has_pellet(game, pos));
    
    game->board[pos.r][pos.c] = ' ';
    game->pelletsRemaining--;
}

int board_count_pellets(const Game* game) {
    assert(game != NULL);
    
    int count = 0;
    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->cols; c++) {
            if (game->board[r][c] == '.') {
                count++;
            }
        }
    }
    return count;
}

char board_get_char(const Game* game, Pos pos) {
    assert(game != NULL);
    
    if (pos.r < 0 || pos.r >= game->rows || pos.c < 0 || pos.c >= game->cols) {
        return ' ';
    }
    
    return game->board[pos.r][pos.c];
}
