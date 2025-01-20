#  GPIO Teclado RP2040

## Descrição

Este repositório contém o código desenvolvido durante o trabalho em grupo no âmbito do programa **Embarca Tech**. O projeto foi realizado com o objetivo de criar um sistema de controle de teclado utilizando o microcontrolador **RP2040**, em que as teclas podem ser configuradas para acionar diferentes funcionalidades através dos pinos GPIO.

## Integrantes do Grupo

- **José Guilherme Marques**: Responsável revisar o código, aprovar os pull requests e criação do Readme.
- **Otiliano Junior**: Responsável pela criação do código C e Diagrama Json
- **Lucas Fialho Xavier**: Responsável por fazer o vídeo de ensaio.
- **Bruno Schumacher**: Responsável por implementar testes.
- **Caio Nunes**: Responsável por implementar testes.

## Requisitos

- **Ambiente de Desenvolvimento**: Utilizar o **VS Code** para desenvolvimento.
- **Linguagem de Programação**: O código foi escrito em **C**, utilizando os recursos do **Pico SDK**.
- **Simulador**: O **simulador Wokwi** deve ser integrado ao VS Code para testar o código em um ambiente virtual antes de executar no hardware real.

## Funcionalidades

- Configuração dos pinos GPIO do RP2040 para mapear as teclas de um teclado matricial.
- Cada tecla acionada executa uma função personalizada, como acionar LEDs ou enviar sinais para outros dispositivos.
- O código usa interrupções para garantir respostas rápidas quando uma tecla é pressionada.

### Vídeo de Ensaio

Aqui está o link para o vídeo de ensaio:

[Vídeo de Ensaio](https://1drv.ms/v/c/187048040209a455/EeaiMoIugI5PvVHaIcv84xsBFnFsCqxsLiWrMhRwkBXPpA?e=LfOace)
Neste vídeo é feita a explicação do código e também é mostrada a simulação.

## Como Instalar

1. Clone o repositório:

   ```bash
   git clone https://github.com/guilhermejnr/gpio-teclado-rp2040
   ```

2. Instale as dependências necessárias:
        - Instale o VS Code.
        - Instale o Pico SDK no ambiente de desenvolvimento.
        - Integre o simulador Wokwi ao VS Code. 

3. Carregue o código no RP2040 após a configuração do ambiente.

## Como Usar
1. Conecte o teclado matricial aos pinos GPIO do RP2040 conforme especificado no código.
2. No VS Code, compile e carregue o código no RP2040.
3. Ao pressionar uma tecla no teclado, a função correspondente será executada.
4. O simulador Wokwi pode ser usado para testar o funcionamento do código sem a necessidade de hardware físico.

## Contribuição
Contribuições são bem-vindas! Se você deseja contribuir para o projeto, por favor, faça um fork do repositório e envie suas alterações via pull request.
