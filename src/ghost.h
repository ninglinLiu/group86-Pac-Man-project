#ifndef GHOST_H
#define GHOST_H

#include "game.h"

/**
 * Ghost AI and movement functions
 */

/**
 * Update all ghosts for one tick
 * @param game - pointer to game structure
 */
void ghost_update_all(Game* game);

/**
 * Update single ghost for one tick
 * @param game - pointer to game structure
 * @param ghostIndex - index of ghost to update
 */
void ghost_update(Game* game, int ghostIndex);

/**
 * Get valid directions for ghost at position
 * @param game - pointer to game structure
 * @param pos - current position
 * @param prevDr - previous row direction
 * @param prevDc - previous column direction
 * @param directions - array to store valid directions
 * @return number of valid directions
 */
int ghost_get_valid_directions(const Game* game, Pos pos, int prevDr, int prevDc, 
                               int directions[4][2]);

/**
 * Move ghost to new position
 * @param game - pointer to game structure
 * @param ghostIndex - index of ghost to move
 * @param newPos - new position
 */
void ghost_move(Game* game, int ghostIndex, Pos newPos);

/**
 * Respawn ghost to starting position
 * @param game - pointer to game structure
 * @param ghostIndex - index of ghost to respawn
 */
void ghost_respawn(Game* game, int ghostIndex);

#endif // GHOST_H
