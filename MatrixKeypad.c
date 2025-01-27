#include "MatrixKeypad.h"
#include "pico/stdlib.h"
#include <stdlib.h>

MatrixKeypad_t *MatrixKeypad_create(char *keymap, uint8_t *rowPins, uint8_t *colPins, uint8_t rown, uint8_t coln) {
    MatrixKeypad_t *keypad;
    uint8_t i;

    keypad = malloc(sizeof(MatrixKeypad_t));
    if (keypad == NULL) {
        return NULL;
    }

    keypad->rown = rown;
    keypad->coln = coln;
    keypad->rowPins = rowPins;
    keypad->colPins = colPins;
    keypad->keyMap = keymap;
    keypad->lastKey = '\0';
    keypad->buffer = '\0';

    for (i = 0; i < keypad->rown; i++) {
        gpio_init(keypad->rowPins[i]);
        gpio_set_dir(keypad->rowPins[i], GPIO_OUT);
        gpio_put(keypad->rowPins[i], 1); // Set row to HIGH
    }

    for (i = 0; i < keypad->coln; i++) {
        gpio_init(keypad->colPins[i]);
        gpio_set_dir(keypad->colPins[i], GPIO_IN);
        gpio_pull_up(keypad->colPins[i]);
    }

    return keypad;
}

void MatrixKeypad_scan(MatrixKeypad_t *keypad) {
    uint8_t row, col;
    char key = '\0';

    if (keypad != NULL) {
        for (row = 0; row < keypad->rown; row++) {
            gpio_put(keypad->rowPins[row], 0); // Set row LOW
            for (col = 0; col < keypad->coln; col++) {
                if (gpio_get(keypad->colPins[col]) == 0) {
                    key = keypad->keyMap[row * keypad->coln + col];
                }
            }
            gpio_put(keypad->rowPins[row], 1); // Set row HIGH
        }

        if (keypad->lastKey != key) {
            keypad->lastKey = key;
            if (key != '\0') {
                keypad->buffer = key;
            }
        }
    }
}

uint8_t MatrixKeypad_hasKey(MatrixKeypad_t *keypad) {
    if (keypad == NULL) {
        return 0;
    }
    return (keypad->buffer != '\0') ? 1 : 0;
}

char MatrixKeypad_getKey(MatrixKeypad_t *keypad) {
    char key;

    if (keypad == NULL) {
        return '\0';
    }

    key = keypad->buffer;
    keypad->buffer = '\0';

    return key;
}

char MatrixKeypad_waitForKey(MatrixKeypad_t *keypad) {
    char key;

    if (keypad == NULL) {
        return '\0';
    }

    while (!MatrixKeypad_hasKey(keypad)) {
        MatrixKeypad_scan(keypad);
        sleep_ms(20); // Add a small delay to avoid busy-waiting
    }

    key = MatrixKeypad_getKey(keypad);
    return key;
}

char MatrixKeypad_waitForKeyTimeout(MatrixKeypad_t *keypad, uint16_t timeout) {
    char key;
    uint32_t start_time = to_ms_since_boot(get_absolute_time());

    if (keypad == NULL) {
        return '\0';
    }

    while (!MatrixKeypad_hasKey(keypad) && (to_ms_since_boot(get_absolute_time()) - start_time <= timeout)) {
        MatrixKeypad_scan(keypad);
        sleep_ms(20);
    }

    key = MatrixKeypad_getKey(keypad);
    return key;
}

void MatrixKeypad_flush(MatrixKeypad_t *keypad) {
    if (keypad != NULL) {
        keypad->buffer = '\0';
    }
}
