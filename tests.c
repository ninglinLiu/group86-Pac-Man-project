#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "src/game.h"
#include "src/render.h"
#include "src/input.h"

/**
 * Test suite for deterministic Pac-Man game
 * Provides three test scenarios with expected outputs
 */

// Test input files
static const char* WIN_INPUT = "tests/win_input.txt";
static const char* DEATH_INPUT = "tests/death_input.txt";
static const char* PELLET_INPUT = "tests/pellet_input.txt";

/**
 * Run a test with input from file
 */
void run_test(const char* test_name, const char* input_file, uint32_t seed, int ghostCount) {
    printf("=== Running %s test ===\n", test_name);
    
    // Initialize game
    Game game;
    game_init(&game, seed, ghostCount);
    
    // Open input file
    FILE* file = fopen(input_file, "r");
    if (!file) {
        printf("Error: Cannot open input file %s\n", input_file);
        return;
    }
    
    // Run game with input from file
    bool running = true;
    while (running && !game_is_won(&game) && !game_is_lost(&game)) {
        int input_char = fgetc(file);
        if (input_char == EOF) break;
        
        char input = (char)toupper(input_char);
        running = game_tick(&game, input);
    }
    
    fclose(file);
    
    // Print result
    printf("RESULT seed=%u ghosts=%d score=%d lives=%d pellets=%d ticks=%lu\n",
           seed, ghostCount, game.score, game.lives, game.pelletsRemaining, game.tick);
    printf("\n");
}

/**
 * Create test input files
 */
void create_test_files(void) {
    // Win test: systematic movement to eat all pellets
    FILE* win_file = fopen(WIN_INPUT, "w");
    if (win_file) {
        // Simple pattern: right, down, left, up (repeat)
        for (int i = 0; i < 200; i++) {
            fputc('D', win_file); // Right
            fputc('S', win_file); // Down
            fputc('A', win_file); // Left
            fputc('W', win_file); // Up
        }
        fclose(win_file);
    }
    
    // Death test: move into ghost
    FILE* death_file = fopen(DEATH_INPUT, "w");
    if (death_file) {
        fputc('D', death_file); // Move right
        fputc('D', death_file); // Move right again
        fputc('Q', death_file); // Quit
        fclose(death_file);
    }
    
    // Pellet test: eat some pellets
    FILE* pellet_file = fopen(PELLET_INPUT, "w");
    if (pellet_file) {
        for (int i = 0; i < 10; i++) {
            fputc('D', pellet_file); // Move right
        }
        fputc('Q', pellet_file); // Quit
        fclose(pellet_file);
    }
}

int main(int argc, char* argv[]) {
    printf("Pac-Man Test Suite\n");
    printf("==================\n\n");
    
    // Create test input files
    create_test_files();
    
    // Run tests with deterministic seeds
    run_test("Win", WIN_INPUT, 12345, 4);
    run_test("Death", DEATH_INPUT, 54321, 2);
    run_test("Pellet", PELLET_INPUT, 99999, 1);
    
    printf("All tests completed!\n");
    return 0;
}
