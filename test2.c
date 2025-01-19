#include <stdio.h>
#include "pico/stdlib.h"

// Declarações das funções que queremos testar
void init_pins();
char get_key();
void perform_action(char key);

void test_get_key()
{
  printf("Iniciando testes de detecção de tecla...\n");

  // Teste 1: Simular a tecla 'A'
  printf("Teste 1: Simular a tecla 'A'\n");
  char key = 'A';      // Valor simulado
  perform_action(key); // Deve ligar o LED verde

  // Teste 2: Simular a tecla 'B'
  printf("Teste 2: Simular a tecla 'B'\n");
  key = 'B';           // Valor simulado
  perform_action(key); // Deve ligar o LED azul

  // Teste 3: Simular a tecla 'C'
  printf("Teste 3: Simular a tecla 'C'\n");
  key = 'C';           // Valor simulado
  perform_action(key); // Deve ligar o LED vermelho

  // Teste 4: Simular a tecla '#'
  printf("Teste 4: Simular a tecla '#'\n");
  key = '#';           // Valor simulado
  perform_action(key); // Deve ativar o buzzer

  // Teste 5: Simular a tecla 'D'
  printf("Teste 5: Simular a tecla 'D'\n");
  key = 'D';           // Valor simulado
  perform_action(key); // Deve ligar todos os LEDs

  // Teste 6: Tecla sem ação
  printf("Teste 6: Tecla sem ação específica (por exemplo, tecla '1')\n");
  key = '1';           // Valor simulado
  perform_action(key); // Deve informar que a tecla não tem ação específica

  printf("Testes de teclas concluídos.\n");
}

void test_perform_action()
{
  printf("Iniciando testes de execução de ações...\n");

  // Testando cada ação de forma separada
  printf("Teste 1: LED verde\n");
  perform_action('A'); // Deve ligar o LED verde

  printf("Teste 2: LED azul\n");
  perform_action('B'); // Deve ligar o LED azul

  printf("Teste 3: LED vermelho\n");
  perform_action('C'); // Deve ligar o LED vermelho

  printf("Teste 4: Ativar o buzzer\n");
  perform_action('#'); // Deve ativar o buzzer

  printf("Teste 5: Ligar todos os LEDs\n");
  perform_action('D'); // Deve ligar todos os LEDs

  printf("Teste 6: Tecla sem ação\n");
  perform_action('1'); // Deve informar que a tecla não tem ação

  printf("Testes de execução de ações concluídos.\n");
}

int main()
{
  stdio_init_all();

  printf("Inicializando testes do sistema...\n");

  // Inicializar os pinos
  init_pins();

  // Testar a função get_key
  test_get_key();

  // Testar a função perform_action
  test_perform_action();

  printf("Todos os testes foram executados.\n");
  return 0;
}
