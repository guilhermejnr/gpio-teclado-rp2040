#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

extern uint row_pins[ROWS];
extern uint col_pins[COLS];

#define LED_RED 13
#define LED_BLUE 12
#define LED_GREEN 11
#define BUZZER 21

extern char keys[ROWS][COLS];

// Protótipos de funções
void init_pins(void);
char get_key(void);
void perform_action(char key);

#endif
