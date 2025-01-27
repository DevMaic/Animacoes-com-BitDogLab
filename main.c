#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "hardware/timer.h"
#include "framesAnimacao.c"

//arquivo .pio
#include "pio_matrix.pio.h"
//define o LED de saída
#define GPIO_LED 13

//parte do código relativa ao teclado matricial
uint columns[4] = {4, 3, 2, 1}; 
uint rows[4] = {8, 7, 6, 5};

//mapa de teclas
char KEY_MAP[16] = {
    '1', '2' , '3', 'A',
    '4', '5' , '6', 'B',
    '7', '8' , '9', 'C',
    '*', '0' , '#', 'D'
};

uint _columns[4];
uint _rows[4];
char _matrix_values[16];
uint all_columns_mask = 0x0;
uint column_mask[4];

//imprimir valor binário
void imprimir_binario(int num) {
    int i;
    for (i = 31; i >= 0; i--) {
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

//fim do código do teclado

//inicio do código relativo a matrix de leds

//número de LEDs
#define NUM_PIXELS 25
//pino de saída
#define OUT_PIN 9

//vetor para criar imagem na matriz de led - 1
double desenho[25] =   {0.0, 0.0, 0.0, 0.0, 1.0,
                        1.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.0, 0.0, 1.0,
                        0.0, 0.0, 0.0, 0.0, 1.0,
                        0.0, 0.0, 0.0, 0.0, 1.0};

double limpaLeds[25] =  {0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.0};

//vetor para criar imagem na matriz de led - 2
double desenho2[25] =   {1.0, 0.0, 0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        1.0, 0.0, 0.0, 0.0, 1.0};


//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g) {
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//rotina para acionar a matrix de leds - ws2812b
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(desenho[24-i], r=0.0, g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(desenho[24-i], r=0.0 , g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
    imprimir_binario(valor_led);
}
//fim do código da matriz de leds

//Funções com as animações dos membros do grupo
void animacaoMaic(double desenho1[], uint32_t valor_led, PIO pio, uint sm, double r, double g, double b) {
    desenho_pio(desenho1, valor_led, pio, sm, r, g, b);
}

void animacaoHumbertoZigZag(PIO pio, uint sm, uint32_t valor_led, double r, double g, double b) {
    // Loop para exibir a animação em loop
    while (true) {
        // Exibe cada frame por 100 ms (FPS = 10)
        for (int i = 0; i < 25; i++) {
            desenho_pio(frames[i], valor_led, pio, sm, r, g, b);
            sleep_ms(100); // Delay para controlar o FPS
        }

        // Volta ao início
        for (int i = 24; i >= 0; i--) {
            desenho_pio(frames[i], valor_led, pio, sm, r, g, b);
            sleep_ms(100); // Delay para controlar o FPS
        }
    }
}


void animacaoGabrielRostoMicrobit(PIO pio, uint sm, uint32_t valor_led, double r, double g, double b) {
    for (int repeat = 0; repeat < 5; repeat++) { // Repetir a animação 5 vezes
        for (int frame = 0; frame < 5; frame++) {
            desenho_pio(frames_rosto_microbit[frame], valor_led, pio, sm, r, g, b);
            sleep_ms(500); // Pausa de 500ms entre os frames
        }
    }
}


//função principal
int main()
{
    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();
    init_teclado();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configuração do teclado
    // pico_keypad_init(columns, rows, KEY_MAP);
    char caracter_press;

    //configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    gpio_init(GPIO_LED);
    gpio_set_dir(GPIO_LED, GPIO_OUT);

    while (true) {
      caracter_press = detectar_tecla();
      printf("\nTecla pressionada: %c\n", caracter_press);

    //   Avaliação de caractere para o LED
      if (caracter_press != '\0') {
            if(caracter_press=='0') {
                animacaoMaic(desenho, valor_led, pio, sm, r, g, b);
                gpio_put(GPIO_LED, false);
            }else if(caracter_press == '1'){
                 animacaoHumbertoZigZag(pio, sm, valor_led, r, g, b);
            }else if (caracter_press == '2') {
                animacaoGabrielRostoMicrobit(pio, sm, valor_led, r, g, b);
            }
        }

      sleep_ms(100);
    }
}