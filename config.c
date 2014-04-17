/* 
 * File:   config.c
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:57
 */
#include <xc.h>
#include "globals.h"

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
    TRISC = 0b10100000;  // Portas RC5(TX) e RC7(AN9) como entrada, restante como sa�da (RC4(RX))
    ANSELC = 0b10000000; // Porta RC7 como anal�gica.

    OPTION_REGbits.nWPUEN = 1;
}

/* Configura os par�metros de convers�o anal�gica-digital */
void configure_Analog() {
    ADON = 0b1;          // Liga a convers�o anal�gica-digital
    ADCON1 = 0b11010111; /* Justifica � direita, converte utilizando o clock FOSC/16,
                          * utiliza pino externo como Vref- e Fixed Voltage Reference (FVR) como Vref+ */
    FVRCON = 0b11000010; /* Fixed Voltage Reference (FVR) est� habilitada, indicador de temperatura desabilitada,
                          * comparador e convers�o digital-anal�gica desabilitada, Vref+ como 2.048V */
}

/*
 * Configura a porta serial.
 *
 * baud_rate: Baude rate desejado.
 * mode: (0) - Modo de baixa velocidade; (1) Modo de alta velocidade.
 *
 * Por padr�o � usado o modo 8 bits e sem paridade, mas se necess�rio ajuste aqui a configura��o desejada.
 * Verifique o datasheet para ver a porcentagem de erro e se a velocidade � possivel para o cristal utilizado.
 */
void configure_SerialPort(long baud_rate, int mode) {
    /* Desabilita as portas I2C e SPI */
    SSP1CON1bits.SSPEN = 0;
    SSP2CON1bits.SSPEN = 0;

    APFCON0bits.RXDTSEL = 0b1; // Define porta RX em RC5(5).
    APFCON0bits.TXCKSEL = 0b1; // Define porta TX em RC4(6).

    /* Inverte polaridade */
    BAUDCONbits.SCKP = 0b1;

    RCSTA = 0b10010000; // Habilita a porta serial, recep��o de 8 bits em modo cont�nuo, ass�ncrono.
    int valor;          // Valor da configura��o para o gerador de baud rate.

    if (mode == 1) {
        /* modo = 1, modo de alta velocidade. */
        TXSTA = 0b00100100;                                   // Modo ass�ncrono, transmiss�o de 8 bits.
        valor = (int) (((_XTAL_FREQ / baud_rate) - 16) / 16); // C�lculo do valor do gerador de baud rate.
    } else {
        /* modo = 0, modo de baixa velocidade. */
        TXSTA = 0b00100000;                                   // Modo ass�ncrono, transmiss�o de 8 bits.
        valor = (int) (((_XTAL_FREQ / baud_rate) - 64) / 64); // C�lculo do valor do gerador de baud rate.
    }
    SPBRG = valor;
    RCIE = 1; // Habilita interrup��o de recep��o.
    TXIE = 0; // Deixa interrup��o de transmiss�o desligada, pois corre se o risco de ter uma interrup��o escrita e leitura ao mesmo tempo.
}

/* Configura as interrup��es. */
void configure_Interrupts() {
    PEIE = 1; // Habilita a interrup��o de perif�ricos do PIC
    GIE = 1;  // Global Interrupt Enable bit

    OPTION_REGbits.INTEDG = 1; // ?
}

/* Configura os timers.
 * Timer 1 � usado para a leitura dos controles.
 * Timer 2 � usado para enviar o sinal para os ESCs.
 */
void configure_Timer() {
    /* Timer 1 is used to read the input from controller */
    T1CON = 0b01000000;

    /* Sets T2CON for delay used when setting the ESC output */
    /* [ - | T2OUTPS <3:0> | TMR2ON | T2CKPS <1:0> ] */
    T2CON = 0b00011001;
    TMR2IE = 1; /* Enable Timer 2 interrupt */
    TMR2IF = 0; /* Reset Timer 2 flag */

    /* Configura��es do Timer 0 - N�o utilizado */
    OPTION_REGbits.TMR0CS = 1;
    OPTION_REGbits.TMR0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b000;
}