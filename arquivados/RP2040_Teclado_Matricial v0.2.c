#include <stdio.h>
#include <pico/stdlib.h>

// Define os pinos das colunas do teclado
const uint8_t COL_PINS[] = {18, 19, 20, 4}; 
const uint8_t ROW_PINS[] = {16, 17, 9, 8};

//// Definição dos pinos
//const uint ROWS[4] = {18, 19, 20, 4}; // GPIOs para linhas
//const uint COLS[4] = {16, 17, 9, 8}; // GPIOs para colunas

// Mapa de teclas 
const char KEY_MAP[4][4] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};

// Função para ler uma tecla do teclado
char read_keypad(uint8_t *cols, uint8_t *rows) {
  for (int i = 0; i < 4; i++) {
    gpio_put(rows[i], 0); // Define o pino da linha como baixo
    uint8_t result = 0;
    for (int j = 0; j < 4; j++) {
      result |= gpio_get(cols[j]); // Lê os estados dos pinos das colunas
    }
    if (result == 0) { // Verifica se alguma coluna está baixa
      // Obtém a tecla usando a posição do bit menos significativo
      char key = KEY_MAP[i][__builtin_ctz(result)]; 
      gpio_put(rows[i], 1); // Define o pino da linha como alto (debounce)
      return key;
    }
    gpio_put(rows[i], 1); // Define o pino da linha como alto
  }
  return 0; // Nenhuma tecla pressionada
}



int main() {

// Inicializa a serial
 uart_init(uart0, 115200);
 stdio_init_all();


    // Inicializa os pinos das colunas como entrada com pull-up
 for (int i = 0; i < sizeof(COL_PINS)/sizeof(COL_PINS[0]); i++) {
    gpio_init(COL_PINS[i]);
    gpio_set_dir(COL_PINS[i], GPIO_IN);
    gpio_pull_up(COL_PINS[i]);
  }

  // Inicializa os pinos das linhas como saída
  for (int i = 0; i < sizeof(ROW_PINS)/sizeof(ROW_PINS[0]); i++) {
    gpio_init(ROW_PINS[i]);
    gpio_set_dir(ROW_PINS[i], GPIO_OUT);
  }

setbuf(stdout, NULL); // Desabilita o buffering de linha

printf("--- Pronto para receber entradas do usuário ---\n");
   while (true) {
        for (int row = 0; row < 4; row++) {
            gpio_put(ROW_PINS[row], 0); // Define a linha como baixo

            // Lê todas as colunas de uma vez para otimizar
            uint8_t columns = 0;
            for (int col = 0; col < 4; col++) {
                columns |= gpio_get(COL_PINS[col]) << col;
            }

            if (columns != 0) {
                int col = __builtin_ctz(columns);
                char key = KEY_MAP[row][col];
                printf("Tecla pressionada: %c\n", key);
                sleep_ms(300); // Debounce
                break; // Sai do loop externo, pois uma tecla foi pressionada
            }

            gpio_put(ROW_PINS[row], 1); // Define a linha como alto
        }
  
}}