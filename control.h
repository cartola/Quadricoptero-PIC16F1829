/* 
 * File:   control.h
 * Author: Eduardo
 * 
 * Responsável pelas funções de leitura do controle
 *
 * Created on 11 de Abril de 2014, 00:41
 */

#ifndef CONTROL_H
#define	CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

// Maximum power of any channel
#define MAX_DURATION 251

#define MIN_WIDTH_CHANNEL1 17506
#define MAX_WIDTH_CHANNEL1 31326
#define MIN_WIDTH_CHANNEL2 17566
#define MAX_WIDTH_CHANNEL2 31446
#define MIN_WIDTH_CHANNEL3 18486
#define MAX_WIDTH_CHANNEL3 30606
#define MIN_WIDTH_CHANNEL4 17706
#define MAX_WIDTH_CHANNEL4 32206

char readChannel1();
char readChannel2();
char readChannel3();
char readChannel4();

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_H */

