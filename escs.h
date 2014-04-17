/* 
 * File:   escs.h
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:49
 */

#ifndef ESCS_H
#define	ESCS_H

#ifdef	__cplusplus
extern "C" {
#endif

void setESC1(char duration);
void setESC2(char duration);
void setESC3(char duration);
void setESC4(char duration);

int escSet = 0;

#ifdef	__cplusplus
}
#endif

#endif	/* ESCS_H */

