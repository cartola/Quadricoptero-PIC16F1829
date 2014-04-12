/* 
 * File:   config.c
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:57
 */
#include <xc.h>

/* Configura o clock do processador. */
void configure_Oscillator() {
    /* Ajusta o clock para 32MHz. */
    /*OSCCONbits.IRCF = 0b00001110; // Define o oscilador interno em 8MHz.
    OSCCONbits.SPLLEN = 0x01; // Liga o PPL 4x.
    OSCCONbits.SCS = 0x00; // Fonte do oscilador definido na configuração FOSC. */

    /* Ajusta o clock para 16MHz. */
    OSCCONbits.IRCF = 0b00001111; // Define o oscilador interno em 16MHz.
    OSCCONbits.SPLLEN = 0x00; // Desliga o PPL 4x.
    OSCCONbits.SCS = 0x00; // Fonte do oscilador definido na configuração FOSC.
}

/* Configura as portas de entrada e saída. */
void configure_Ports() {
    /* Porta A */
    TRISA = 0b00010100;  // Portas RA2 e RA4 como entradas, restante como saída.
    ANSELA = 0b00010100; // Portas RA2 e RA4 como analógicas.

    /* Porta B */
    TRISB = 0b11110000;  // Portas RB0 ... RB3 como saída e RB4 ... RB7 como entrada.
    ANSELB = 0b00000000; // Todas as portas como I/O digitais.

    /* Porta C */
    TRISC = 0b10000000;  // Porta RC7 como entrada, restante como saída.
    ANSELC = 0b10000000; // Porta RC7 como analógica.
}

/* Configura os parâmetros de conversão analógica-digital */
void configure_Analog() {
    ADON = 0b1;          // Liga a conversão analógica-digital
    ADCON1 = 0b11010111; /* Justifica à direita, converte utilizando o clock FOSC/16,
                          * utiliza pino externo como Vref- e Fixed Voltage Reference (FVR) como Vref+ */
    FVRCON = 0b11000010; /* Fixed Voltage Reference (FVR) está habilitada, indicador de temperatura desabilitada,
                          * comparador e conversão digital-analógica desabilitada, Vref+ como 2.048V */
}