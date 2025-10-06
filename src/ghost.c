#include "ghost.h"
#include "board.h"
#include "rng.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

void ghost_update_all(Game* game) {
    assert(game != NULL);
    
    for (int i = 0; i < game->ghostCount; i++) {
        if (game->ghosts[i].alive) {
            ghost_update(game, i);
        }
    }
}

void ghost_update(Game* game, int ghostIndex) {
    assert(game != NULL);
    assert(ghostIndex >= 0 && ghostIndex < game->ghostCount);
    
    Entity* ghost = &game->ghosts[ghostIndex];
    if (!ghost->alive) return;
    
    // Get valid directions (avoid immediate reversal)
    int directions[4][2];
    int validCount = ghost_get_valid_directions(game, ghost->pos, ghost->dr, ghost->dc, directions);
    
    if (validCount == 0) {
        // No valid moves, stay in place
        return;
    }
    
    // Choose random direction
    int choice = rng_choice(validCount);
    int newDr = directions[choice][0];
    int newDc = directions[choice][1];
    
    // Calculate new position
    Pos newPos = {ghost->pos.r + newDr, ghost->pos.c + newDc};
    
    // Move ghost
    ghost_move(game, ghostIndex, newPos);
}

int ghost_get_valid_directions(const Game* game, Pos pos, int prevDr, int prevDc, 
                               int directions[4][2]) {
    assert(game != NULL);
    assert(directions != NULL);
    
    int validCount = 0;
    int allDirections[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
    
    for (int i = 0; i < 4; i++) {
        int dr = allDirections[i][0];
        int dc = allDirections[i][1];
        
        // Skip immediate reversal unless it's the only option
        if (dr == -prevDr && dc == -prevDc) {
            continue;
        }
        
        Pos newPos = {pos.r + dr, pos.c + dc};
        if (board_is_valid_pos(game, newPos)) {
            directions[validCount][0] = dr;
            directions[validCount][1] = dc;
            validCount++;
        }
    }
    
    // If no valid directions (except reversal), allow reversal
    if (validCount == 0) {
        Pos reversePos = {pos.r - prevDr, pos.c - prevDc};
        if (board_is_valid_pos(game, reversePos)) {
            directions[0][0] = -prevDr;
            directions[0][1] = -prevDc;
            validCount = 1;
        }
    }
    
    return validCount;
}

void ghost_move(Game* game, int ghostIndex, Pos newPos) {
    assert(game != NULL);
    assert(ghostIndex >= 0 && ghostIndex < game->ghostCount);
    assert(board_is_valid_pos(game, newPos));
    
    Entity* ghost = &game->ghosts[ghostIndex];
    
    // Update direction
    ghost->dr = newPos.r - ghost->pos.r;
    ghost->dc = newPos.c - ghost->pos.c;
    
    // Update position
    ghost->pos = newPos;
}

void ghost_respawn(Game* game, int ghostIndex) {
    assert(game != NULL);
    assert(ghostIndex >= 0 && ghostIndex < game->ghostCount);
    
    Entity* ghost = &game->ghosts[ghostIndex];
    ghost->pos = ghost->start;
    ghost->dr = 0;
    ghost->dc = 0;
    ghost->alive = true;
}
