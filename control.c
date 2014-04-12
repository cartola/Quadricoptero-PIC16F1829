/* 
 * File:   control.c
 * Author: Eduardo
 *
 * Responsável pelas funções de leitura do controle
 * 
 * Created on 11 de Abril de 2014, 00:41
 */
#include <xc.h>
#include "control.h"
#include "globals.h"

/* Calculates the duration of the signal from control1 */
char readChannel1() {
    int duration;

    TMR1 = 0;

    while (RB4); /* Wait for low */
    while (!RB4); /* Wait for high */

    TMR1ON = TRUE; /* Enable timer 1 to count the time */
    while (RB4);
    TMR1ON = FALSE; /* Disable timer 1 */

    /* Min = 17506 */
    /* Max = 31326 */
    duration = TMR1;
    if (duration > MAX_WIDTH_CHANNEL1) {
        duration = MAX_WIDTH_CHANNEL1;
    } else if (duration < MIN_WIDTH_CHANNEL1) {
        duration = MIN_WIDTH_CHANNEL1;
    }

    duration = (int) ((duration - MIN_WIDTH_CHANNEL1) / 54);

    return (char) duration;
}

/* Calculates the duration of the signal from control2 */
char readChannel2() {
    int duration;

    TMR1 = 0;

    while (RB5); /* Wait for low */
    while (!RB5); /* Wait for high */

    TMR1ON = TRUE; /* Enable timer 1 to count the time */
    while (RB5);
    TMR1ON = FALSE; /* Disable timer 1 */

    /* Min = 17566 */
    /* Max = 31446 */
    duration = TMR1;
    if (duration > MAX_WIDTH_CHANNEL2) {
        duration = MAX_WIDTH_CHANNEL2;
    } else if (duration < MIN_WIDTH_CHANNEL2) {
        duration = MIN_WIDTH_CHANNEL2;
    }

    duration = (int) ((duration - MIN_WIDTH_CHANNEL2) / 54);

    return (char) duration;
}

/* Calculates the duration of the signal from control3 */
char readChannel3() {
    int duration;

    TMR1 = 0;

    while (RB6); /* Wait for low */
    while (!RB6); /* Wait for high */

    TMR1ON = TRUE; /* Enable timer 1 to count the time */
    while (RB6);
    TMR1ON = FALSE; /* Disable timer 1 */

    /* Min = 18486 */
    /* Max = 30606 */
    duration = TMR1;
    if (duration > MAX_WIDTH_CHANNEL3) {
        duration = MAX_WIDTH_CHANNEL3;
    } else if (duration < MIN_WIDTH_CHANNEL3) {
        duration = MIN_WIDTH_CHANNEL3;
    }

    duration = (int) ((duration - MIN_WIDTH_CHANNEL3) / 48);

    return (char) duration;
}

/* Calculates the duration of the signal from control4 */
char readChannel4() {
    int duration;

    TMR1 = 0;

    while (RB7); /* Wait for low */
    while (!RB7); /* Wait for high */

    TMR1ON = TRUE; /* Enable timer 1 to count the time */
    while (RB7);
    TMR1ON = FALSE; /* Disable timer 1 */

    /* Min = 17706 */
    /* Max = 32206 */
    duration = TMR1;
    if (duration > MAX_WIDTH_CHANNEL4) {
        duration = MAX_WIDTH_CHANNEL4;
    } else if (duration < MIN_WIDTH_CHANNEL4) {
        duration = MIN_WIDTH_CHANNEL4;
    }

    duration = (int) ((duration - MIN_WIDTH_CHANNEL4) / 57);

    return (char) duration;
}
