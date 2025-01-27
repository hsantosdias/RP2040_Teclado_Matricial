#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"


// Definição dos pinos
const uint ROWS[4] = {18, 19, 20, 4}; // GPIOs para linhas
const uint COLS[4] = {16, 17, 9, 8}; // GPIOs para colunas

//const uint LINHAS[4] = {18, 19, 20, 4}; 
//const uint COLUNAS[4] = {16, 17, 9, 8};

// Função para inicializar os pinos
void inicializar_gpio() {
    for (int i = 0; i < 4; i++) {
        // Configura os pinos das linhas como saída
        gpio_init(ROWS[i]);
        gpio_set_dir(ROWS[i], true); // Saída
        gpio_put(ROWS[i], false);    // Inicializa como desligado

        // Configura os pinos das colunas como entrada com pull-down
        gpio_init(COLS[i]);
        gpio_set_dir(COLS[i], false); // Entrada
        gpio_pull_down(COLS[i]);
    }
}

// Função para ler o teclado matricial
char ler_teclado() {
    char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };

    for (int row = 0; row < 4; row++) {
        // Ativa a linha atual
        gpio_put(ROWS[row], true);

        for (int col = 0; col < 4; col++) {
            if (gpio_get(COLS[col])) {
                gpio_put(ROWS[row], false);
                return keys[row][col];
            }
        }

        // Desativa a linha
        gpio_put(ROWS[row], false);
    }

    return '\0'; // Nenhuma tecla pressionada
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura os GPIOs
    inicializar_gpio();

    // Loop principal
    while (1) {
        char tecla = ler_teclado();
        if (tecla != '\0') {
            printf("Tecla pressionada: %c\n", tecla);
        }
        sleep_ms(100); // Pequeno delay para evitar leitura contínua
    }

    return 0;
}
