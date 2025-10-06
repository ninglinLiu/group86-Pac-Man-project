#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "src/game.h"
#include "src/render.h"
#include "src/input.h"

/**
 * Print usage information
 */
void print_usage(const char* program_name) {
    printf("Usage: %s [-s <seed>] [-g <ghostCount>]\n", program_name);
    printf("  -s <seed>      : RNG seed (default: 12345)\n");
    printf("  -g <ghostCount>: Number of ghosts 1-4 (default: 4)\n");
    printf("  -h             : Show this help\n");
    printf("\nControls:\n");
    printf("  W/A/S/D : Move Pac-Man\n");
    printf("  Q       : Quit game\n");
}

/**
 * Parse command line arguments
 */
int parse_args(int argc, char* argv[], uint32_t* seed, int* ghostCount) {
    *seed = 12345;
    *ghostCount = 4;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            return 1; // Show help
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 < argc) {
                *seed = (uint32_t)strtoul(argv[i + 1], NULL, 10);
                i++; // Skip next argument
            } else {
                fprintf(stderr, "Error: -s requires a seed value\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-g") == 0) {
            if (i + 1 < argc) {
                *ghostCount = (int)strtol(argv[i + 1], NULL, 10);
                if (*ghostCount < 1 || *ghostCount > 4) {
                    fprintf(stderr, "Error: ghost count must be 1-4\n");
                    return -1;
                }
                i++; // Skip next argument
            } else {
                fprintf(stderr, "Error: -g requires a ghost count value\n");
                return -1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            return -1;
        }
    }
    
    return 0; // Success
}

/**
 * Main game loop
 */
int main(int argc, char* argv[]) {
    uint32_t seed;
    int ghostCount;
    
    // Parse command line arguments
    int parse_result = parse_args(argc, argv, &seed, &ghostCount);
    if (parse_result == 1) {
        print_usage(argv[0]);
        return 0;
    } else if (parse_result == -1) {
        return 1;
    }
    
    // Initialize game
    Game game;
    game_init(&game, seed, ghostCount);
    
    printf("Pac-Man Game Started!\n");
    printf("Seed: %u, Ghosts: %d\n", seed, ghostCount);
    printf("Press any key to start...\n");
    getchar();
    
    // Main game loop
    bool running = true;
    while (running && !game_is_won(&game) && !game_is_lost(&game)) {
        render_clear_screen();
        render_board(&game);
        render_status(&game);
        
        printf("Enter move (W/A/S/D) or Q to quit: ");
        fflush(stdout);
        
        char input = input_read();
        running = game_tick(&game, input);
        
        // Consume newline after input
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    // Game over
    render_clear_screen();
    render_board(&game);
    render_status(&game);
    
    if (game_is_won(&game)) {
        render_win(&game);
    } else if (game_is_lost(&game)) {
        render_game_over(&game);
    }
    
    printf("RESULT seed=%u ghosts=%d score=%d lives=%d pellets=%d ticks=%lu\n",
           seed, ghostCount, game.score, game.lives, game.pelletsRemaining, game.tick);
    
    return 0;
}
