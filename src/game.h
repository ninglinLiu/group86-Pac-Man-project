#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Position structure for entities on the board
 */
typedef struct {
    int r;  // row
    int c;  // column
} Pos;

/**
 * Entity structure for Pac-Man and ghosts
 */
typedef struct {
    Pos pos;     // current position
    Pos start;   // starting position
    int dr;      // direction row delta
    int dc;      // direction column delta
    bool alive;  // whether entity is alive
} Entity;

/**
 * Main game state structure
 */
typedef struct {
    int rows, cols;           // board dimensions
    char board[25][40];       // game board (max 25x40)
    Entity pac;               // Pac-Man entity
    Entity ghosts[4];         // ghost entities
    int ghostCount;           // number of active ghosts
    int score;                // current score
    int lives;                // remaining lives
    int pelletsRemaining;     // pellets left to collect
    uint32_t rng_state;       // RNG state for deterministic behavior
    unsigned long tick;       // game tick counter
} Game;

/**
 * Initialize a new game with given parameters
 * @param game - pointer to game structure to initialize
 * @param seed - RNG seed for deterministic behavior
 * @param ghostCount - number of ghosts (1-4)
 */
void game_init(Game* game, uint32_t seed, int ghostCount);

/**
 * Update game state for one tick
 * @param game - pointer to game structure
 * @param input - input character (W/A/S/D/Q)
 * @return true if game should continue, false if should quit
 */
bool game_tick(Game* game, char input);

/**
 * Check if game is won (all pellets collected)
 * @param game - pointer to game structure
 * @return true if game is won
 */
bool game_is_won(const Game* game);

/**
 * Check if game is lost (no lives remaining)
 * @param game - pointer to game structure
 * @return true if game is lost
 */
bool game_is_lost(const Game* game);

/**
 * Check collision between Pac-Man and any ghost
 * @param game - pointer to game structure
 * @return true if collision detected
 */
bool game_check_collision(const Game* game);

/**
 * Handle collision: lose life and respawn entities
 * @param game - pointer to game structure
 */
void game_handle_collision(Game* game);

#endif // GAME_H
