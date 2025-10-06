#include "input.h"
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

char input_read(void) {
    int c = getchar();
    if (c == EOF) return 'Q'; // Treat EOF as quit
    
    char input = (char)toupper(c);
    
    // Validate input
    if (input == 'W' || input == 'A' || input == 'S' || input == 'D' || input == 'Q') {
        return input;
    }
    
    return 0; // Invalid input
}

bool input_to_direction(char input, int* dr, int* dc) {
    assert(dr != NULL);
    assert(dc != NULL);
    
    switch (input) {
        case 'W':
            *dr = -1; *dc = 0;  // Up
            return true;
        case 'S':
            *dr = 1; *dc = 0;   // Down
            return true;
        case 'A':
            *dr = 0; *dc = -1;  // Left
            return true;
        case 'D':
            *dr = 0; *dc = 1;   // Right
            return true;
        default:
            return false;
    }
}

bool input_is_movement(char input) {
    return input == 'W' || input == 'A' || input == 'S' || input == 'D';
}

bool input_is_quit(char input) {
    return input == 'Q';
}
