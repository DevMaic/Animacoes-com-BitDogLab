#ifndef ANIMACOES_KAIQUE_H
#define ANIMACOES_KAIQUE_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pio_matrix.pio.h"

// Declaração da função desenho_pio (definida no arquivo principal)
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

// Matrizes das animações
double desenho2[25] = {0.0, 1.0, 0.0, 1.0, 0.0,
                       1.0, 0.0, 1.0, 0.0, 1.0,
                       1.0, 0.0, 0.0, 0.0, 1.0,
                       0.0, 1.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 1.0, 0.0, 0.0};

double L[25] = {1.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0, 0.0};

double O[25] = {1.0, 1.0, 1.0, 1.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0, 1.0};

double V[25] = {1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 0.0, 0.0, 0.0, 1.0,
                0.0, 0.0, 1.0, 0.0, 0.0};

double E[25] = {1.0, 1.0, 1.0, 1.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 1.0,
                1.0, 1.0, 1.0, 1.0, 0.0};

// Função para exibir a animação do Kaique (LOVE)
void animacaoKaique(uint32_t valor_led, PIO pio, uint sm)
{
    double r = 1.0, g = 0.0, b = 0.0;
    desenho_pio(desenho2, valor_led, pio, sm, r, g, b);
    sleep_ms(2000);
    
    desenho_pio(L, valor_led, pio, sm, r, g, b);
    sleep_ms(2000);
    
    desenho_pio(O, valor_led, pio, sm, r, g, b);
    sleep_ms(2000);
    
    desenho_pio(V, valor_led, pio, sm, r, g, b);
    sleep_ms(2000);
    
    desenho_pio(E, valor_led, pio, sm, r, g, b);
    sleep_ms(2000);
}

#endif
