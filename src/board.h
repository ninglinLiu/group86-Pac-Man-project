#ifndef BOARD_H
#define BOARD_H

#include "game.h"

/**
 * Board management functions
 */

/**
 * Load the static map into game board
 * @param game - pointer to game structure
 */
void board_load(Game* game);

/**
 * Check if position is valid (within bounds and not a wall)
 * @param game - pointer to game structure
 * @param pos - position to check
 * @return true if position is valid
 */
bool board_is_valid_pos(const Game* game, Pos pos);

/**
 * Check if position is a wall
 * @param game - pointer to game structure
 * @param pos - position to check
 * @return true if position is a wall
 */
bool board_is_wall(const Game* game, Pos pos);

/**
 * Check if position has a pellet
 * @param game - pointer to game structure
 * @param pos - position to check
 * @return true if position has a pellet
 */
bool board_has_pellet(const Game* game, Pos pos);

/**
 * Remove pellet from position
 * @param game - pointer to game structure
 * @param pos - position to remove pellet from
 */
void board_remove_pellet(Game* game, Pos pos);

/**
 * Count total pellets on board
 * @param game - pointer to game structure
 * @return number of pellets
 */
int board_count_pellets(const Game* game);

/**
 * Get character at position (for rendering)
 * @param game - pointer to game structure
 * @param pos - position to check
 * @return character at position
 */
char board_get_char(const Game* game, Pos pos);

#endif // BOARD_H
