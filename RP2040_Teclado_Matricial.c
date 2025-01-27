#include <stdio.h>
#include "pico/stdlib.h"
#include "MatrixKeypad.h"

// Configuração do teclado matricial
#define ROWSPIN 4
#define COLSPIN 4

// Definição dos pinos GPIO conectados às linhas e colunas do teclado
uint8_t rowPins[ROWSPIN] = {18, 19, 20, 4};  // GPIOs para as linhas
uint8_t colPins[COLSPIN] ={16, 17, 9, 8};  // GPIOs para as colunas

// Mapeamento das teclas (4x4)
char keyMap[ROWSPIN][COLSPIN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

int main() {
    // Inicialização do sistema (UART para debug e outros periféricos)
    stdio_init_all();

    // Criação do objeto MatrixKeypad
    MatrixKeypad_t *keypad = MatrixKeypad_create((char *)keyMap, rowPins, colPins, ROWSPIN, COLSPIN);
    if (keypad == NULL) {
        printf("Erro: Falha ao inicializar o teclado matricial!\n");
        return 1;
    }

    printf("Teclado matricial iniciado. Pressione uma tecla:\n");

    while (true) {
        // Escaneia o teclado
        MatrixKeypad_scan(keypad);

        // Verifica se uma tecla foi pressionada
        if (MatrixKeypad_hasKey(keypad)) {
            char key = MatrixKeypad_getKey(keypad);  // Obtém a tecla pressionada
            printf("Tecla pressionada: %c\n", key);
        }

        // Delay para evitar leituras repetidas
        sleep_ms(100);
    }

    return 0;
}
