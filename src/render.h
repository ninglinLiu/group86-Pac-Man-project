#ifndef RENDER_H
#define RENDER_H

#include "game.h"

/**
 * Rendering functions for ASCII display
 */

/**
 * Render the game board with entities
 * @param game - pointer to game structure
 */
void render_board(const Game* game);

/**
 * Render the status line (score, lives, pellets, tick)
 * @param game - pointer to game structure
 */
void render_status(const Game* game);

/**
 * Clear the screen (portable method using newlines)
 */
void render_clear_screen(void);

/**
 * Render game over message
 * @param game - pointer to game structure
 */
void render_game_over(const Game* game);

/**
 * Render win message
 * @param game - pointer to game structure
 */
void render_win(const Game* game);

#endif // RENDER_H
