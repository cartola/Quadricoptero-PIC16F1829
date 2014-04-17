/* 
 * File:   serial.c
 * Author: Eduardo
 *
 * Created on 16 de Abril de 2014, 23:14
 */

#include "serial.h"
#include <xc.h>

/* Envia um caracter via porta serial. */
void putch(char data) {
    while(!TXIF) // Aguarda liberar o buffer
        continue;
    TXREG = data;
}
