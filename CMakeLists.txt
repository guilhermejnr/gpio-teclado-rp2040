# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Definir a versão mínima do CMake
cmake_minimum_required(VERSION 3.13)

# Definir os padrões de C e C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializar o SDK da Raspberry Pi Pico a partir da localização instalada
# (observe que isso pode vir de variáveis de ambiente, cache do CMake, etc.)

# == NÃO EDITE AS LINHAS ABAIXO para que a extensão VSCode da Raspberry Pi Pico funcione ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Definir o tipo de board (neste caso, uma placa Pico W)
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importar o SDK da Raspberry Pi Pico (deve ser antes de definir o projeto)
include(pico_sdk_import.cmake)

# Definir o nome do projeto
project(GPIO-TECLADO-RP2040 C CXX ASM)

# Inicializar o SDK da Raspberry Pi Pico
pico_sdk_init()

# Adicionar o executável. O nome do executável será o mesmo nome do projeto.
add_executable(GPIO-TECLADO-RP2040 main.c)

# Definir o nome e versão do programa
pico_set_program_name(GPIO-TECLADO-RP2040 "GPIO-TECLADO-RP2040")
pico_set_program_version(GPIO-TECLADO-RP2040 "0.1")

# Ativar saída via UART/USB
pico_enable_stdio_uart(GPIO-TECLADO-RP2040 1)
pico_enable_stdio_usb(GPIO-TECLADO-RP2040 1)

# Adicionar a biblioteca padrão ao projeto
target_link_libraries(GPIO-TECLADO-RP2040
        pico_stdlib
        hardware_pwm
)

# Adicionar os arquivos de inclusão padrão ao projeto
target_include_directories(GPIO-TECLADO-RP2040 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Adicionar bibliotecas solicitadas pelo usuário (se houver)
target_link_libraries(GPIO-TECLADO-RP2040 
        # Aqui você pode adicionar outras bibliotecas, se necessário
)

# Adicionar saídas extras para o projeto
pico_add_extra_outputs(GPIO-TECLADO-RP2040)
