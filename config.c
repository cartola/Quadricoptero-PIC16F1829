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
    OSCCONbits.SCS = 0x00; // Fonte do oscilador definido na configura��o FOSC. */

    /* Ajusta o clock para 16MHz. */
    OSCCONbits.IRCF = 0b00001111; // Define o oscilador interno em 16MHz.
    OSCCONbits.SPLLEN = 0x00; // Desliga o PPL 4x.
    OSCCONbits.SCS = 0x00; // Fonte do oscilador definido na configura��o FOSC.
}

/* Configura as portas de entrada e sa�da. */
void configure_Ports() {
    /* Porta A */
    TRISA = 0b00010100;  // Portas RA2 e RA4 como entradas, restante como sa�da.
    ANSELA = 0b00010100; // Portas RA2 e RA4 como anal�gicas.

    /* Porta B */
    TRISB = 0b11110000;  // Portas RB0 ... RB3 como sa�da e RB4 ... RB7 como entrada.
    ANSELB = 0b00000000; // Todas as portas como I/O digitais.

    /* Porta C */
    TRISC = 0b10000000;  // Porta RC7 como entrada, restante como sa�da.
    ANSELC = 0b10000000; // Porta RC7 como anal�gica.
}

/* Configura os par�metros de convers�o anal�gica-digital */
void configure_Analog() {
    ADON = 0b1;          // Liga a convers�o anal�gica-digital
    ADCON1 = 0b11010111; /* Justifica � direita, converte utilizando o clock FOSC/16,
                          * utiliza pino externo como Vref- e Fixed Voltage Reference (FVR) como Vref+ */
    FVRCON = 0b11000010; /* Fixed Voltage Reference (FVR) est� habilitada, indicador de temperatura desabilitada,
                          * comparador e convers�o digital-anal�gica desabilitada, Vref+ como 2.048V */
}