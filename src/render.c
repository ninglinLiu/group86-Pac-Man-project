#include "render.h"
#include "board.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

void render_board(const Game* game) {
    assert(game != NULL);
    
    // Create display board (copy of game board)
    char display[25][40];
    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->cols; c++) {
            display[r][c] = game->board[r][c];
        }
    }
    
    // Overlay Pac-Man
    if (game->pac.alive) {
        display[game->pac.pos.r][game->pac.pos.c] = 'P';
    }
    
    // Overlay ghosts
    for (int i = 0; i < game->ghostCount; i++) {
        if (game->ghosts[i].alive) {
            display[game->ghosts[i].pos.r][game->ghosts[i].pos.c] = 'G';
        }
    }
    
    // Print board
    for (int r = 0; r < game->rows; r++) {
        for (int c = 0; c < game->cols; c++) {
            putchar(display[r][c]);
        }
        putchar('\n');
    }
}

void render_status(const Game* game) {
    assert(game != NULL);
    
    printf("Score: %4d Lives: %d Pellets: %3d Tick: %3lu\n",
           game->score, game->lives, game->pelletsRemaining, game->tick);
}

void render_clear_screen(void) {
    // Portable screen clear using newlines
    for (int i = 0; i < 50; i++) {
        putchar('\n');
    }
}

void render_game_over(const Game* game) {
    assert(game != NULL);
    
    printf("\n=== GAME OVER ===\n");
    printf("Final Score: %d\n", game->score);
    printf("Final Tick: %lu\n", game->tick);
}

void render_win(const Game* game) {
    assert(game != NULL);
    
    printf("\n=== YOU WIN! ===\n");
    printf("Final Score: %d\n", game->score);
    printf("Final Tick: %lu\n", game->tick);
}
