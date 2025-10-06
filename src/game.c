#include "game.h"
#include "board.h"
#include "input.h"
#include "ghost.h"
#include "rng.h"
#include "maps.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void game_init(Game* game, uint32_t seed, int ghostCount) {
    assert(game != NULL);
    assert(ghostCount >= 1 && ghostCount <= 4);
    
    // Initialize RNG
    rng_seed(seed);
    game->rng_state = seed;
    
    // Load board
    board_load(game);
    
    // Initialize Pac-Man
    game->pac.pos.r = PAC_START_ROW;
    game->pac.pos.c = PAC_START_COL;
    game->pac.start.r = PAC_START_ROW;
    game->pac.start.c = PAC_START_COL;
    game->pac.dr = 0;
    game->pac.dc = 0;
    game->pac.alive = true;
    
    // Initialize ghosts
    int ghostStartRows[] = GHOST_START_ROWS;
    int ghostStartCols[] = GHOST_START_COLS;
    game->ghostCount = ghostCount;
    
    for (int i = 0; i < ghostCount; i++) {
        game->ghosts[i].pos.r = ghostStartRows[i];
        game->ghosts[i].pos.c = ghostStartCols[i];
        game->ghosts[i].start.r = ghostStartRows[i];
        game->ghosts[i].start.c = ghostStartCols[i];
        game->ghosts[i].dr = 0;
        game->ghosts[i].dc = 0;
        game->ghosts[i].alive = true;
    }
    
    // Initialize game state
    game->score = 0;
    game->lives = 3;
    game->tick = 0;
}

bool game_tick(Game* game, char input) {
    assert(game != NULL);
    
    game->tick++;
    
    // Handle quit
    if (input_is_quit(input)) {
        return false;
    }
    
    // Handle Pac-Man movement
    if (input_is_movement(input) && game->pac.alive) {
        int dr, dc;
        if (input_to_direction(input, &dr, &dc)) {
            Pos newPos = {game->pac.pos.r + dr, game->pac.pos.c + dc};
            if (board_is_valid_pos(game, newPos)) {
                game->pac.pos = newPos;
                game->pac.dr = dr;
                game->pac.dc = dc;
                
                // Check for pellet
                if (board_has_pellet(game, newPos)) {
                    board_remove_pellet(game, newPos);
                    game->score += 10;
                }
            }
        }
    }
    
    // Update ghosts
    ghost_update_all(game);
    
    // Check for collisions
    if (game_check_collision(game)) {
        game_handle_collision(game);
    }
    
    return true;
}

bool game_is_won(const Game* game) {
    assert(game != NULL);
    return game->pelletsRemaining == 0;
}

bool game_is_lost(const Game* game) {
    assert(game != NULL);
    return game->lives == 0;
}

bool game_check_collision(const Game* game) {
    assert(game != NULL);
    
    if (!game->pac.alive) return false;
    
    for (int i = 0; i < game->ghostCount; i++) {
        if (game->ghosts[i].alive &&
            game->pac.pos.r == game->ghosts[i].pos.r &&
            game->pac.pos.c == game->ghosts[i].pos.c) {
            return true;
        }
    }
    
    return false;
}

void game_handle_collision(Game* game) {
    assert(game != NULL);
    
    game->lives--;
    
    // Respawn Pac-Man
    game->pac.pos = game->pac.start;
    game->pac.dr = 0;
    game->pac.dc = 0;
    game->pac.alive = true;
    
    // Respawn all ghosts
    for (int i = 0; i < game->ghostCount; i++) {
        ghost_respawn(game, i);
    }
}
