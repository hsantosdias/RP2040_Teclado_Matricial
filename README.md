# RP2040_Teclado_Matricial
Implementação de um teclado matricial no RP2040


```c
#include <stdio.h>

// Definição da estrutura pixel
typedef struct {
    int LINHAS;
    int COLUNA;
} Pixel;

// Função para capturar dados simulados do teclado matricial 4x4
void capturar_teclado(Pixel *matriz, int linhas, int colunas) {
    printf("Digite os valores para o teclado matricial 4x4 (total %d valores):\n", linhas * colunas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("Entre o valor para Pixel[%d][%d]: ", i, j);
            scanf("%d", &(matriz[i * colunas + j].LINHAS)); // Armazena o valor nas LINHAS (exemplo)
            matriz[i * colunas + j].COLUNA = j;             // Atribui a coluna correspondente
        }
    }
}

// Função para exibir os dados armazenados na matriz
void exibir_matriz(Pixel *matriz, int linhas, int colunas) {
    printf("\nMatriz capturada:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("[%d][%d]: %d\t", i, j, matriz[i * colunas + j].LINHAS);
        }
        printf("\n");
    }
}

int main() {
    const int LINHAS = 4;
    const int COLUNAS = 4;

    // Alocação de memória para a matriz 4x4
    Pixel matriz[LINHAS * COLUNAS];

    // Capturar dados do teclado matricial
    capturar_teclado(matriz, LINHAS, COLUNAS);

    // Exibir a matriz capturada
    exibir_matriz(matriz, LINHAS, COLUNAS);

    return 0;
}

```

## Explicação
1. Definição da Estrutura Pixel:

- A estrutura tem dois campos: LINHAS e COLUNA. Estes são utilizados para armazenar as coordenadas ou valores do teclado matricial.

2. Função capturar_teclado:

- Simula a entrada do teclado matricial pedindo os valores via terminal.
- Preenche os valores na matriz utilizando aritmética de ponteiros para navegar nos índices.
3. Função exibir_matriz:

- Exibe a matriz capturada no formato [linha][coluna]: valor.
4. Entrada e Saída Simulada:

O código simula a entrada do teclado matricial, mas pode ser adaptado para capturar os sinais reais de um teclado conectado ao hardware.

## Exemplo de UsoExemplo de Uso
Se você executar o código, ele solicitará entradas como:

    Entre o valor para Pixel[0][0]: 1
    Entre o valor para Pixel[0][1]: 2
    ...
    Entre o valor para Pixel[3][3]: 16

E exibirá a matriz capturada:

    Matriz capturada:
    [0][0]: 1  [0][1]: 2	 [0][2]: 3	[0][3]:  4	
    [1][0]: 5  [1][1]: 6	 [1][2]: 7	[1][3]:  8	
    [2][0]: 9  [2][1]: 10	[2][2]: 11	[2][3]: 12	
    [3][0]: 13 [3][1]: 14	[3][2]: 15	[3][3]: 16
    
