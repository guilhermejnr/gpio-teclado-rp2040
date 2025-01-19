#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

// Define os pinos usados para as linhas e colunas do teclado matricial
uint row_pins[ROWS] = {8, 7, 6, 5}; // R1, R2, R3, R4
uint col_pins[COLS] = {4, 3, 2, 28};  // C1, C2, C3, C4

// Definir pinos dos LEDs e do buzzer
#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11
#define BUZZER 21

// Mapeamento das teclas
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para inicializar os pinos
void init_pins() {
    // Configurar pinos das linhas como saída
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1); // Desativa a linha inicialmente
    }

    // Configurar pinos das colunas como entrada com pull-up
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }

    // Configurar pinos dos LEDs e do buzzer
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0);

    // Inicializar a comunicação serial (UART)
    stdio_init_all();

    printf("Pinos inicializados com sucesso.\n");
}

// Função para detectar tecla pressionada
char get_key() {
    for (int row = 0; row < ROWS; row++) {
        // Ativar a linha atual
        gpio_put(row_pins[row], 0);

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col]) == 0) { // Checar se a coluna está em nível baixo
                // Aguarda para debounce
                sleep_ms(100);
                while (gpio_get(col_pins[col]) == 0);
                // Desativa a linha
                gpio_put(row_pins[row], 1);
                printf("Tecla detectada: %c (Linha: %d, Coluna: %d)\n", keys[row][col], row, col);
                return keys[row][col];
            }
        }

        // Desativar a linha
        gpio_put(row_pins[row], 1);
    }

    return 0; // Nenhuma tecla pressionada
}

void perform_action(char key) {
    // Desligar tudo inicialmente
    gpio_put(LED_RED, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(BUZZER, 0);

    printf("Executando ação para tecla: %c\n", key);

    switch (key) {
        case 'A':
            gpio_put(LED_GREEN, 1);
            printf("LED verde ligado.\n");
            break;
        case 'B':
            gpio_put(LED_BLUE, 1);
            printf("LED azul ligado.\n");
            break;
        case 'C':
            gpio_put(LED_RED, 1);
            printf("LED vermelho ligado.\n");
            break;
        case '#':
            printf("Buzzer ativado.\n");
            for (int i = 0; i < 5; i++) {
                gpio_put(BUZZER, 1);
                sleep_ms(100);
                gpio_put(BUZZER, 0);
                sleep_ms(100);
            }
            break;
        case 'D':
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);
            gpio_put(LED_BLUE, 1);
            printf("Todos os LEDs ligados.\n");
            break;
        default:
            printf("Tecla %c pressionada, mas sem ação específica.\n", key);
            break;
    }
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial

    init_pins();

    printf("Sistema inicializado. Pressione teclas no teclado matricial.\n");

    while (1) {
        char key = get_key();
        if (key) {
            perform_action(key);
        }
        sleep_ms(100);
    }
    return 0;
}