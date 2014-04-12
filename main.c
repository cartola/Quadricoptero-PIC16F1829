/*
 * Author: Eduardo Camargo
 * Controlling a quadricopter
 */
#include <xc.h>
#include <stdlib.h>  // Funções matemáticas básicas como abs
#include <stdio.h>   // Funções de I/O para o RS-232
#include "config.h"  // Configurações iniciais do PIC
#include "globals.h" // Constantes globais
#include "control.h" // Funções de leitura do controle
#include "escs.h"    // Funções de escrita nos ESCs
#include "gyros.h"   // Funções de leitura dos gyroscópios

/* Importante: _XTAL_FREQ Definido no globals.h */

//__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & LVP_OFF);
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

/* Valor que define o quando os controles estão em respouso */
#define MIDDLE_CHANNEL1 128
#define MIDDLE_CHANNEL2 132
#define MIDDLE_CHANNEL4 128

#define COEF_FORWARD 10
#define COEF_BACKWARD 10
#define COEF_LEFT 10
#define COEF_RIGHT 10
#define COEF_CLOCKWISE 10
#define COEF_CCLOCKWISE 10

#define RANGE_GYRO_STILL 1

char filter(int duration);
void readAndSet();
void calculate();
void teste();

unsigned int fl_exit = FALSE;

char inputControl1; /* Rotate CW and CCW */
char inputControl2; /* Back and forward */
char inputControl3; /* Throtlle */
char inputControl4; /* Left and right */

int zeroGyroPitch;
int zeroGyroRoll;
int zeroGyroYaw;

int motor1 = 1;
int motor2 = 1;
int motor3 = 1;
int motor4 = 1;

int pitch;
int roll;
int yaw;

int yawAcc = 0;

long yawAccTeste = 0;
long count = 0;
int result = -1;

void main() {
    configure_Oscillator();
    configure_Ports();
    configure_Analog;

    /* [ RBPU | INTEDG | T0CS | T0SE | PSA | PS2 | PS1 | PS0 ] */
    OPTION_REG = 0b11010000;

    /* Timer 1 is used to read the input from controller */
    T1CON = 0b01000000;

    /* Sets T2CON for delay used when setting the ESC output */
    /* [ - | T2OUTPS <3:0> | TMR2ON | T2CKPS <1:0> ] */
    T2CON = 0b00011001;
    TMR2IE = 1; /* Enable Timer 2 interrupt */
    TMR2IF = 0; /* Reset Timer 2 flag */

    /* [ GIE | PEIE | TMR0IE | INTE | IOCIE | TMR0IF | INTF | IOCIF ]*/
    INTCON = 0b00000000; /* Enable interruption */

    /* [ IOCBP7 | IOCBP6 | IOCBP5 | IOCBP4 | - | - | - | - ] */
    IOCBP = 0b00000000; /* Enable interrupt on change positive */

    /* [ IOCBN7 | IOCBN6 | IOCBN5 | IOCBN4 | - | - | - | - ] */
    IOCBN = 0b00000000; /* Enable interrupt on change negative */

    RA0 = 0;
    /* Wait for internal clock stabilization */
    while (!HFIOFR);

    //calibrateGyros();

    while (TRUE) {
        readAndSet();
        calculate();

        gyroReadNumber++;
        pitch = readGyroPitch(FALSE);
        roll = readGyroRoll(FALSE);
        yaw = readGyroYaw(FALSE);

        if (gyroReadNumber >= MAX_GRYO_VALUES) {
            gyroReadNumber = 0;
        }
    }
}

/* Garantees duration between 1 and 251 */
char filter(int duration) {
    if (duration < 1) {
        duration = 1;
    }
    else if (duration > MAX_DURATION) {
        duration = MAX_DURATION;
    }

    return duration;
}

void readAndSet() {
    inputControl1 = readChannel1();
    setESC1(motor1);
    setESC2(motor2);
    setESC3(motor3);
    setESC4(motor4);

    inputControl2 = readChannel2();
    setESC1(motor1);
    setESC2(motor2);
    setESC3(motor3);
    setESC4(motor4);

    inputControl3 = readChannel3();
    setESC1(motor1);
    setESC2(motor2);
    setESC3(motor3);
    setESC4(motor4);

    inputControl4 = readChannel4();
    setESC1(motor1);
    setESC2(motor2);
    setESC3(motor3);
    setESC4(motor4);

    /* Just for test */
    /*	inputControl1 = readChannel1();
            setESC1(1);
            setESC2(1);
            setESC3(1);
            setESC4(1);
            inputControl2 = readChannel2();
            setESC1(1);
            setESC2(1);
            setESC3(1);
            setESC4(1);
            inputControl3 = readChannel3();
            setESC1(1);
            setESC2(1);
            setESC3(1);
            setESC4(1);
            inputControl4 = readChannel4();
            setESC1(1);
            setESC2(1);
            setESC3(1);
            setESC4(1);*/
}

// void calculate()
// {
// 	inputControl1 = filter(inputControl1);
// 	inputControl2 = filter(inputControl2);
// 	inputControl3 = filter(inputControl3);
// 	inputControl4 = filter(inputControl4);
// 
// 	/* Setting the throttle */
// 	motor1 = motor2 = motor3 = motor4 = inputControl3;
// 	
// 	/* Forward and backward */
// 	motor1 = (char)(inputControl3 + inputControl3 * ((float)(inputControl2 - MIDDLE_CHANNEL2)/MIDDLE_CHANNEL2/COEF_FORWARD));
// 	motor2 = (char)(inputControl3 + inputControl3 * ((float)(inputControl2 - MIDDLE_CHANNEL2)/MIDDLE_CHANNEL2/COEF_FORWARD));
// 	motor3 = (char)(inputControl3 - inputControl3 * ((float)(inputControl2 - MIDDLE_CHANNEL2)/MIDDLE_CHANNEL2/COEF_BACKWARD));
// 	motor4 = (char)(inputControl3 - inputControl3 * ((float)(inputControl2 - MIDDLE_CHANNEL2)/MIDDLE_CHANNEL2/COEF_BACKWARD));
// 
// 	/* Left and rigth */
// 	motor2 = (char)(motor2 + motor2 * ((float)(inputControl4 - MIDDLE_CHANNEL4)/MIDDLE_CHANNEL4/COEF_RIGHT));
// 	motor3 = (char)(motor3 + motor3 * ((float)(inputControl4 - MIDDLE_CHANNEL4)/MIDDLE_CHANNEL4/COEF_RIGHT));
// 	motor1 = (char)(motor1 - motor1 * ((float)(inputControl4 - MIDDLE_CHANNEL4)/MIDDLE_CHANNEL4/COEF_LEFT));
// 	motor4 = (char)(motor4 - motor4 * ((float)(inputControl4 - MIDDLE_CHANNEL4)/MIDDLE_CHANNEL4/COEF_LEFT));
// 
// 	/* Rotate */
// 	motor1 = (char)(motor1 - motor1 * ((float)(inputControl1 - MIDDLE_CHANNEL1)/MIDDLE_CHANNEL1/COEF_CLOCKWISE));
// 	motor3 = (char)(motor3 - motor3 * ((float)(inputControl1 - MIDDLE_CHANNEL1)/MIDDLE_CHANNEL1/COEF_CLOCKWISE));
// 	motor4 = (char)(motor4 + motor4 * ((float)(inputControl1 - MIDDLE_CHANNEL1)/MIDDLE_CHANNEL1/COEF_CCLOCKWISE));
// 	motor2 = (char)(motor2 + motor2 * ((float)(inputControl1 - MIDDLE_CHANNEL1)/MIDDLE_CHANNEL1/COEF_CCLOCKWISE));
// 
// 	motor1 = filter(motor1);
// 	motor2 = filter(motor2);
// 	motor3 = filter(motor3);
// 	motor4 = filter(motor4);
// }



void calculate() {
    int pitchAux = pitch;
    int rollAux = roll;
    int yawControl = yaw;    

    inputControl1 = filter(inputControl1); /* Yaw */
    inputControl2 = filter(inputControl2); /* Pitch */
    inputControl3 = filter(inputControl3); /* Throttle */
    inputControl4 = filter(inputControl4); /* Roll */

    motor1 = motor2 = motor3 = motor4 = inputControl3;
    pitchAux += ((inputControl2 - MIDDLE_CHANNEL2) / 2);
    rollAux += ((inputControl4 - MIDDLE_CHANNEL4) / 2);
    yawControl += ((inputControl1 - MIDDLE_CHANNEL1) / 2);

    /*if (!((pitchAux > zeroGyroPitch - RANGE_GYRO_STILL) && (pitchAux < zeroGyroPitch + RANGE_GYRO_STILL)))
    {
    //if (pitch > zeroGyroPitch)
            motor1 += ((pitchAux - zeroGyroPitch)/8);
            motor2 += ((pitchAux - zeroGyroPitch)/8);
            motor3 -= ((pitchAux - zeroGyroPitch)/8);
            motor4 -= ((pitchAux - zeroGyroPitch)/8);
    }

    if (!((rollAux > zeroGyroRoll - RANGE_GYRO_STILL) && (rollAux < zeroGyroRoll + RANGE_GYRO_STILL)))
    {
            motor1 -= ((rollAux - zeroGyroRoll)/8);
            motor4 -= ((rollAux - zeroGyroRoll)/8);
            motor2 += ((rollAux - zeroGyroRoll)/8);
            motor3 += ((rollAux - zeroGyroRoll)/8);
    }

    if (!((yawAux > zeroGyroYaw - RANGE_GYRO_STILL) && (yawAux < zeroGyroYaw + RANGE_GYRO_STILL)))
    {
            motor1 += ((yawAux - zeroGyroYaw)/8);
            motor3 += ((yawAux - zeroGyroYaw)/8);
            motor2 -= ((yawAux - zeroGyroYaw)/8);
            motor4 -= ((yawAux - zeroGyroYaw)/8);
    }*/

    if (abs(yaw - zeroGyroYaw) > RANGE_GYRO_STILL) {
        if (yaw > zeroGyroYaw) {
            /* Está girando no sentido horário(?) */
            yawAcc += 1;
        } else {
            /* Está girando no sentido anti-horário(?) */
            yawAcc -= 1;
        }
    }

    motor1 += yawAcc;
    motor3 += yawAcc;
    motor2 -= yawAcc;
    motor4 -= yawAcc;

    if ((inputControl3 > 5) && (inputControl3 < 15)) {
        calibrateGyros();
    }

    if (inputControl3 < 5) {
        motor1 = motor2 = motor3 = motor4 = 0;
        yawAcc = 0;
        yawAccTeste = 0;
        count = 0;
    }
    teste();
    /*if (!((yawControl > zeroGyroYaw - RANGE_GYRO_STILL) && (yawControl < zeroGyroYaw + RANGE_GYRO_STILL)))
    {
        motor1 += ((yawAux - zeroGyroYaw)/8);
        motor3 += ((yawAux - zeroGyroYaw)/8);
        motor2 -= ((yawAux - zeroGyroYaw)/8);
        motor4 -= ((yawAux - zeroGyroYaw)/8);
    }*/

    motor1 = filter(motor1);
    motor2 = filter(motor2);
    motor3 = filter(motor3);
    motor4 = filter(motor4);
   // motor1 = motor2 = motor3 = motor4 = 0;
}

void teste() {

    yawAccTeste += yaw;
    count++;

    if (count > 100) {
        result = yawAccTeste/count;
    }
}
