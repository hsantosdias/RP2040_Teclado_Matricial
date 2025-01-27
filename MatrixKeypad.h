#ifndef MATRIXKEYPAD_H
#define MATRIXKEYPAD_H

#include <stdint.h>

// Define GPIO functions
typedef struct {
    uint8_t rown; 
    uint8_t coln;
    uint8_t *rowPins;
    uint8_t *colPins;
    char *keyMap;
    char lastKey;
    char buffer;
} MatrixKeypad_t;

MatrixKeypad_t *MatrixKeypad_create(char *keymap, uint8_t *rowPins, uint8_t *colPins, uint8_t rown, uint8_t coln);
void MatrixKeypad_scan(MatrixKeypad_t *keypad);
uint8_t MatrixKeypad_hasKey(MatrixKeypad_t *keypad);
char MatrixKeypad_getKey(MatrixKeypad_t *keypad);
char MatrixKeypad_waitForKey(MatrixKeypad_t *keypad);
char MatrixKeypad_waitForKeyTimeout(MatrixKeypad_t *keypad, uint16_t timeout);
void MatrixKeypad_flush(MatrixKeypad_t *keypad);

#endif
