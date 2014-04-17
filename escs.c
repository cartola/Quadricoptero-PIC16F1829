/*
 * File:   escs.c
 * Author: Eduardo
 *
 * Responsável pelas funções de escrita nos ESCs
 *
 * Created on 11 de Abril de 2014, 00:41
 */

#include <xc.h>
#include "escs.h"
#include "globals.h"

/* Sets the ESC with the correct signal.
 * The signal lenght must be between 1ms to 2ms. */
void setESC1(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC1 = ON; /* Turn on RC1 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!escSet); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC1 = OFF; /* Turn off RC1 */
    escSet = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal.
 * The signal lenght must be between 1ms to 2ms. */
void setESC2(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC2 = ON; /* Turn on RC2 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!escSet); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC2 = OFF; /* Turn off RC2 */
    escSet = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal.
 * The signal lenght must be between 1ms to 2ms. */
void setESC3(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC3 = ON; /* Turn on RC3 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!escSet); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC3 = OFF; /* Turn off RC3 */
    escSet = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal.
 * The signal lenght must be between 1ms to 2ms. */
void setESC4(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RA5 = ON; /* Turn on RA5 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!escSet); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RA5 = OFF; /* Turn off RA5 */
    escSet = FALSE; /* Reset the interrupt flag */
}