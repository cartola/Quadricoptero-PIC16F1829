/* 
 * File:   config.h
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:57
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

void configure_Oscillator();
void configure_Ports();
void configure_Analog();
void configure_SerialPort(long baud_rate, int mode);
void configure_Interrupts();
void configure_Timer();

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

