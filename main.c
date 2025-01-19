#include <stdio.h>                // Biblioteca padrão para entrada e saída
#include "pico/stdlib.h"          // Biblioteca da Raspberry Pi Pico para funções padrão (GPIO, delays, etc.)
#include "hardware/pwm.h"         // Biblioteca para manipular o PWM (modulação por largura de pulso)
#include "hardware/clocks.h"      // Biblioteca para gerenciar os clocks da Raspberry Pi Pico
#include "pico/bootrom.h"         // Biblioteca para entrar no modo bootloader

// Definições das portas GPIO dos LEDs
#define GREEN_LED_PIN 11          // Pino do LED verde
#define BLUE_LED_PIN 12           // Pino do LED azul
#define RED_LED_PIN 13            // Pino do LED vermelho

// Definição da porta GPIO do BUZZER
#define BUZZER_PIN 21             // Pino do buzzer

// Define os GPIOs para as linhas e colunas do teclado matricial 4x4
#define ROWS 4                    // Quantidade de linhas do teclado
#define COLS 4                    // Quantidade de colunas do teclado

// Mapear GPIOs para linhas e colunas
const uint8_t row_pins[ROWS] = {8, 7, 6, 5}; // GPIOs usados para as linhas
const uint8_t col_pins[COLS] = {4, 3, 2, 1}; // GPIOs usados para as colunas

// Matriz de teclas do teclado matricial
const char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},         // Primeira linha do teclado
    {'4', '5', '6', 'B'},         // Segunda linha do teclado
    {'7', '8', '9', 'C'},         // Terceira linha do teclado
    {'*', '0', '#', 'D'}          // Quarta linha do teclado
};

// Inicializa os GPIOs do teclado matricial
void init_gpio() {
    // Configura as linhas como saída
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);              // Inicializa o GPIO da linha
        gpio_set_dir(row_pins[i], GPIO_OUT); // Configura como saída
        gpio_put(row_pins[i], 1);            // Inicializa a linha em HIGH
    }

    // Configura as colunas como entrada
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);              // Inicializa o GPIO da coluna
        gpio_set_dir(col_pins[i], GPIO_IN);  // Configura como entrada
        gpio_pull_up(col_pins[i]);           // Ativa o pull-up interno
    }
}

// Inicializa LEDs e Buzzer
void init_leds_and_buzzer() {
    gpio_init(GREEN_LED_PIN);                // Inicializa o pino do LED verde
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);   // Configura como saída
    gpio_put(GREEN_LED_PIN, 0);              // Desliga o LED verde

    gpio_init(BLUE_LED_PIN);                 // Inicializa o pino do LED azul
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);    // Configura como saída
    gpio_put(BLUE_LED_PIN, 0);               // Desliga o LED azul

    gpio_init(RED_LED_PIN);                  // Inicializa o pino do LED vermelho
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);     // Configura como saída
    gpio_put(RED_LED_PIN, 0);                // Desliga o LED vermelho

    gpio_init(BUZZER_PIN);                   // Inicializa o pino do buzzer
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);      // Configura como saída
    gpio_put(BUZZER_PIN, 0);                 // Desliga o buzzer
}

// Configura o PWM no pino do buzzer com uma frequência especificada
void set_buzzer_frequency(uint pin, uint frequency) {
    uint slice_num = pwm_gpio_to_slice_num(pin);            // Obtém o slice de PWM do pino
    gpio_set_function(pin, GPIO_FUNC_PWM);                  // Configura o pino para função PWM
    pwm_config config = pwm_get_default_config();           // Obtém a configuração padrão de PWM
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Ajusta o divisor de clock
    pwm_init(slice_num, &config, true);                     // Inicializa o PWM no slice configurado
    pwm_set_gpio_level(pin, 0);                             // Define o nível inicial como 0
}

// Ativa o buzzer
void start_buzzer(uint pin, uint frequency) {
    set_buzzer_frequency(pin, frequency);    // Configura a frequência do buzzer
    pwm_set_gpio_level(pin, 2048);           // Define o duty cycle em 50% (meia potência)
}

// Desativa o buzzer
void stop_buzzer(uint pin) {
    pwm_set_gpio_level(pin, 0);              // Define o duty cycle como 0 (buzzer desligado)
}

// Varre o teclado matricial para verificar qual tecla está pressionada
char scan_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 0);          // Configura a linha atual como LOW

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col]) == 0) { // Verifica se a coluna está em LOW
                gpio_put(row_pins[row], 1);     // Restaura a linha para HIGH
                return key_map[row][col];      // Retorna a tecla correspondente
            }
        }

        gpio_put(row_pins[row], 1);          // Restaura a linha para HIGH
    }

    return '\0';                             // Retorna '\0' se nenhuma tecla for pressionada
}

// Controla os LEDs e o Buzzer com base na tecla pressionada
void control_leds_and_buzzer(char key) {
    switch (key) {
        case 'A':                            // Acende apenas o LED verde
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(BLUE_LED_PIN, 0);
            gpio_put(RED_LED_PIN, 0);
            break;
        case 'B':                            // Acende apenas o LED azul
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(BLUE_LED_PIN, 1);
            gpio_put(RED_LED_PIN, 0);
            break;
        case 'C':                            // Acende apenas o LED vermelho
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(BLUE_LED_PIN, 0);
            gpio_put(RED_LED_PIN, 1);
            break;
        case 'D':                            // Acende todos os LEDs
            gpio_put(GREEN_LED_PIN, 1);
            gpio_put(BLUE_LED_PIN, 1);
            gpio_put(RED_LED_PIN, 1);
            break;
        case '#':                            // Ativa o buzzer
            start_buzzer(BUZZER_PIN, 440);   // Liga o buzzer com frequência de 440 Hz
            break;
        case '*':                            // Entra no modo bootloader
            printf("Entrando no modo bootloader...\n");
            reset_usb_boot(0, 0);            // Reinicia a placa no modo bootloader
            break;
        default:                             // Desliga os LEDs e o buzzer
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(BLUE_LED_PIN, 0);
            gpio_put(RED_LED_PIN, 0);
            stop_buzzer(BUZZER_PIN);         // Desliga o buzzer
            break;
    }
}

// Função principal
int main() {
    stdio_init_all();                        // Inicializa a comunicação UART
    init_gpio();                             // Inicializa os GPIOs do teclado
    init_leds_and_buzzer();                  // Inicializa os LEDs e o buzzer

    printf("Teclado Matricial 4x4 Controle de LEDs e Buzzer Iniciado.\n");

    char previous_key = '\0';                // Armazena a tecla previamente pressionada

    while (1) {                              // Loop infinito
        char current_key = scan_keypad();    // Verifica qual tecla está pressionada

        if (current_key != previous_key) {   // Verifica se a tecla mudou
            if (current_key != '\0') {       // Se uma tecla foi pressionada
                printf("Tecla pressionada: %c\n", current_key);
            }
            control_leds_and_buzzer(current_key); // Controla LEDs e buzzer
            previous_key = current_key;      // Atualiza a tecla anterior
        }

        sleep_ms(50);                        // Delay para debounce
    }

    return 0;
}
