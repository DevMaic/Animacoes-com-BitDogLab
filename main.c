#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"
//frames das animações
#include "framesAnimacao.c"
//arquivo .pio
#include "pio_matrix.pio.h"
// define o LED de saída
#define GPIO_LED 13

// parte do código relativa ao teclado matricial
uint columns[4] = {4, 3, 2, 1};
uint rows[4] = {8, 7, 6, 5};

// mapa de teclas
char KEY_MAP[16] = {
    '1', '2', '3', 'A',
    '4', '5', '6', 'B',
    '7', '8', '9', 'C',
    '*', '0', '#', 'D'};

uint _columns[4];
uint _rows[4];
char _matrix_values[16];
uint all_columns_mask = 0x0;
uint column_mask[4];

// imprimir valor binário
void imprimir_binario(int num)
{
    int i;
    for (i = 31; i >= 0; i--)
    {
        (num & (1 << i)) ? printf("1") : printf("0");
    }
}

void init_teclado()
{
    // Configura as colunas como saída
    for (int i = 0; i < 4; i++)
    {
        gpio_init(columns[i]);              // Inicializa as colunas
        gpio_set_dir(columns[i], GPIO_OUT); // Configura como saída
        gpio_put(columns[i], 1);            // Inicializa como HIGH (1)
    }

    // Configura as linhas como entrada com pull-up
    for (int i = 0; i < 4; i++)
    {
        gpio_init(rows[i]);             // Inicializa as linhas
        gpio_set_dir(rows[i], GPIO_IN); // Configura como entrada
        gpio_pull_up(rows[i]);
    }
}

char detectar_tecla()
{
    for (int col = 0; col < 4; col++)
    {
        // Ativa a coluna atual
        gpio_put(columns[col], 0);

        // Verifica as linhas
        for (int row = 0; row < 4; row++)
        {
            if (gpio_get(rows[row]) == 0)
            { // Tecla pressionada
                // Desativa a coluna antes de retornar
                gpio_put(columns[col], 1);
                return KEY_MAP[row * 4 + col];
            }
        }

        // Desativa a coluna atual
        gpio_put(columns[col], 1);
    }

    // Nenhuma tecla pressionada
    return '\0';
}

// fim do código do teclado

// inicio do código relativo a matrix de leds

// número de LEDs
#define NUM_PIXELS 25
// pino de saída
#define OUT_PIN 9

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if(r==1.0 && g==1.0 && b==1.0)
        {
            valor_led = matrix_rgb(desenho[24 - i], desenho[24 - i], desenho[24 - i]);
            pio_sm_put_blocking(pio, sm, valor_led);
        } else {
            if (b == 1.0)
            {
                valor_led = matrix_rgb(desenho[24 - i], r = 0.0, g = 0.0);
                pio_sm_put_blocking(pio, sm, valor_led);
            }
            if(r == 1.0)
            {
                valor_led = matrix_rgb(b = 0.0, desenho[24 - i], g = 0.0);
                pio_sm_put_blocking(pio, sm, valor_led);
            }
            if(g == 1.0)
            {
                valor_led = matrix_rgb(b = 0.0, r = 0.0, desenho[24 - i]);
                pio_sm_put_blocking(pio, sm, valor_led);
            }
        }
    }
    imprimir_binario(valor_led);
}
// fim do código da matriz de leds

// Funções com as animações dos membros do grupo
void animacaoMaic(uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    // Exibe cada frame por 100 ms (FPS = 10)
    for (int i = 0; i < 25; i++) {
        desenho_pio(framesMaic[i], valor_led, pio, sm, r, g, 1);
        sleep_ms(100); // Delay para controlar o FPS
    }

    // Volta ao início
    for (int i = 24; i >= 0; i--) {
        desenho_pio(framesMaic[i], valor_led, pio, sm, r, g, 1);
        sleep_ms(100); // Delay para controlar o FPS
    }
}

// Função animação da tecla 3
void animacao_tecla_3(PIO pio, uint sm, uint32_t valor_led, double r, double g, double b, int fps)
{
    // Definição dos frames da animação ao apertar a tecla 3
    double frame_t3_1[25] = {1.0, 0.0, 0.0, 0.0, 0.0,
                             1.0, 0.0, 0.0, 0.0, 0.0,
                             1.0, 0.0, 0.0, 0.0, 0.0,
                             1.0, 0.0, 0.0, 0.0, 0.0,
                             1.0, 0.0, 0.0, 0.0, 0.0};

    double frame_t3_2[25] = {0.0, 1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0, 0.0,
                             0.0, 1.0, 0.0, 0.0, 0.0};

    double frame_t3_3[25] = {0.0, 0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0, 0.0};

    double frame_t3_4[25] = {0.0, 0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0, 0.0};

    double frame_t3_5[25] = {0.0, 0.0, 0.0, 0.0, 1.0,
                             0.0, 0.0, 0.0, 0.0, 1.0,
                             0.0, 0.0, 0.0, 0.0, 1.0,
                             0.0, 0.0, 0.0, 0.0, 1.0,
                             0.0, 0.0, 0.0, 0.0, 1.0};
    // Fim definição dos frames da animação ao apertar a tecla 3

    // Vetor de frames
    double *frames[5] = {frame_t3_1, frame_t3_2, frame_t3_3, frame_t3_4, frame_t3_5};
    int frame_index = 0;
    int contador = 0;

    // Loop para alternar os frames
    while (contador < 50)
    {
        // Atualiza os LEDs com o frame atual
        desenho_pio(frames[frame_index], valor_led, pio, sm, r, g, b);

        // Passa para o próximo frame
        frame_index = (frame_index + 1) % 5; // Alterna entre 0 a 4

        // Espera até o próximo quadro para manter o FPS
        sleep_ms(1000 / fps);

        contador++;
    }
}
// Fim da função animação da tecla 3

void animacaoHumbertoZigZag(PIO pio, uint sm, uint32_t valor_led, double r, double g, double b) {
    // Exibe cada frame por 100 ms (FPS = 10)
    for (int i = 0; i < 25; i++) {
        desenho_pio(framesHumberto[i], valor_led, pio, sm, r, g, b);
        sleep_ms(100); // Delay para controlar o FPS
    }

    // Volta ao início
    for (int i = 24; i >= 0; i--) {
        desenho_pio(framesHumberto[i], valor_led, pio, sm, r, g, b);
        sleep_ms(100); // Delay para controlar o FPS
    }
}

//função principal
int main()
{
    PIO pio = pio0;
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0, g = 0.0;

    // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();
    init_teclado();

    printf("iniciando a transmissão PIO");
    if (ok)
        printf("clock set to %ld\n", clock_get_hz(clk_sys));

    // configuração do teclado
    char caracter_press;

    // configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    gpio_init(GPIO_LED);
    gpio_set_dir(GPIO_LED, GPIO_OUT);

    while (true)
    {
        caracter_press = detectar_tecla();
        printf("\nTecla pressionada: %c\n", caracter_press);

        //   Avaliação de caractere para o LED
        if (caracter_press != '\0')
        {
            if(caracter_press == '0') {
                animacaoMaic(valor_led, pio, sm, r, g, 1);
            } else if(caracter_press == '1') {
                 animacaoHumbertoZigZag(pio, sm, valor_led, r, g, 1);
            } else if(caracter_press == '3') {
                animacao_tecla_3(pio, sm, valor_led, r, g, 1, 10);
            } else if(caracter_press == 'A') {
                desenho_pio(desenhoTeclaA, valor_led, pio, sm, r, g, 1);
            } else if(caracter_press == 'B') {
                desenho_pio(desenhoTeclaB, valor_led, pio, sm, r, g, 1);
            } else if(caracter_press == 'C') {
                desenho_pio(desenhoTeclaC, valor_led, pio, sm, 1, g, b);
            } else if(caracter_press == 'D') {
                desenho_pio(desenhoTeclaD, valor_led, pio, sm, r, 1, b);
            } else if(caracter_press == '#') {
                desenho_pio(desenhoTeclaSerquilha, valor_led, pio, sm, 1, 1, 1);
            }
        }
        sleep_ms(100);
    }
}