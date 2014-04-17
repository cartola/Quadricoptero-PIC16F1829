/* 
 * File:   gyros.c
 * Author: Eduardo
 *
 * Created on 11 de Abril de 2014, 00:52
 */
#include <htc.h>
#include "globals.h"
#include "gyros.h"

int pitchAux = 0;
int rollAux = 0;
int yawAux = 0;



/* Read the gyroscope for pitch (forward and backward) */
int readGyroPitch(short calibration) {
    int voltage;
    int test = 0;
    ADCON0 = 0b00001001; // Start analogic reading for RA2 / AN2
    GO_nDONE = 1;
    while (GO_nDONE); // Wait for reading]

    voltage = ADRESH;
    voltage *= 256;
    voltage += ADRESL;

    if (calibration) {
        return voltage;
    }

    pitchAux += voltage;
    if (gyroReadNumber >= MAX_GRYO_VALUES) {
        pitch = pitchAux / MAX_GRYO_VALUES;
        pitchAux = 0;
    }

    return pitch;
}

/* Read the gyroscope for roll (left and right) */
int readGyroRoll(short calibration) {
    int voltage;

    ADCON0 = 0b00001111; // Start analogic reading for RA4 / AN3
    while (GO_nDONE); // Wait for reading
    voltage = ADRESH;
    voltage *= 256;
    voltage += ADRESL;

    if (calibration) {
        return voltage;
    }

    rollAux += voltage;
    if (gyroReadNumber >= MAX_GRYO_VALUES) {
        roll = rollAux / MAX_GRYO_VALUES;
        rollAux = 0;
    }

    return roll;
}

/* Read the gyroscope for roll (clockwise and counterclockwise) */
int readGyroYaw(short calibration) {
    int voltage;

    ADCON0 = 0b00100111; // Start analogic reading for RC7 / AN9
    while (GO_nDONE); // Wait for reading
    voltage = ADRESH;
    voltage *= 256;
    voltage += ADRESL;

    if (calibration) {
        return voltage;
    }

    yawAux += voltage;
    if (gyroReadNumber >= MAX_GRYO_VALUES) {
        yaw = yawAux / MAX_GRYO_VALUES;
        yawAux = 0;
    }

    return yaw;
}

void calibrateGyros() {
    __delay_ms(5);
    zeroGyroPitch = readGyroPitch(TRUE);
    zeroGyroRoll = readGyroRoll(TRUE);
    __delay_ms(1);
    zeroGyroYaw = readGyroYaw(TRUE);

    pitch = zeroGyroPitch;
    roll = zeroGyroRoll;
    yaw = zeroGyroYaw;
}

