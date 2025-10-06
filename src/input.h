#ifndef INPUT_H
#define INPUT_H

/**
 * Input handling functions
 */

/**
 * Read and validate input character
 * @return validated input character (W/A/S/D/Q) or 0 for invalid
 */
char input_read(void);

/**
 * Convert input character to direction deltas
 * @param input - input character
 * @param dr - pointer to row delta
 * @param dc - pointer to column delta
 * @return true if input is valid movement
 */
bool input_to_direction(char input, int* dr, int* dc);

/**
 * Check if input is valid movement
 * @param input - input character
 * @return true if input is valid movement
 */
bool input_is_movement(char input);

/**
 * Check if input is quit command
 * @param input - input character
 * @return true if input is quit command
 */
bool input_is_quit(char input);

#endif // INPUT_H
