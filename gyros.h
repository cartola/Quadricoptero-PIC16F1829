/* 
 * File:   gyros.h
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:53
 */

#ifndef GYROS_H
#define	GYROS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_GRYO_VALUES 1
    
int readGyroPitch(short calibration);
int readGyroRoll(short calibration);
int readGyroYaw(short calibration);
void calibrateGyros();
int gyroReadNumber = 0;
int zeroGyroPitch;
int zeroGyroRoll;
int zeroGyroYaw;

int pitch;
int roll;
int yaw;

#ifdef	__cplusplus
}
#endif

#endif	/* GYROS_H */

