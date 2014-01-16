/*
 * Author: Eduardo Camargo
 * Controlling a quadricopter
 */
#include <xc.h>
#include <htc.h>
#include <stdlib.h>
//#include <pic16f1829.h>


__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & LVP_OFF);

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

#define _XTAL_FREQ 16000000

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

#define MIDDLE_CHANNEL1 128
#define MIDDLE_CHANNEL2 132
#define MIDDLE_CHANNEL4 128

#define COEF_FORWARD 10
#define COEF_BACKWARD 10
#define COEF_LEFT 10
#define COEF_RIGHT 10
#define COEF_CLOCKWISE 10
#define COEF_CCLOCKWISE 10

#define COEF_GYRO_CCLOCKWISE 10
#define COEF_GYRO_CCLOCKWISE 10
#define COEF_GYRO_CCLOCKWISE 10

#define MAX_GRYO_VALUES 1
#define RANGE_GYRO_STILL 1

char readChannel1();
char readChannel2();
char readChannel3();
char readChannel4();
void resetESC();
void setESC1(char duration);
void setESC2(char duration);
void setESC3(char duration);
void setESC4(char duration);
char filter(int duration);
void readAndSet();
void calculate();
int readGyroPitch(short calibration);
int readGyroRoll(short calibration);
int readGyroYaw(short calibration);
void calibrateGyros();
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
int pitchAux = 0;
int rollAux = 0;
int yawAux = 0;
int yawAcc = 0;
int gyroReadNumber = 0;

long yawAccTeste = 0;
long count = 0;
int result = -1;

void main() {
    /* Internal clock 16MHz */
    /* [ SPLLEN | IRCF<3:0> | - | SCS<1:0> ] */
    OSCCON = 0b01111111;

    TRISB = 0b11110000;
    ANSELB = 0b00000000;
    TRISC = 0b00000000;

    /* ANALOG - RA2 and RA4 Analog */
    TRISA = 0b00010100;
    ANSELA = 0b00010100;

    /* ANALOG - RC7 Analog */
    TRISC = 0b10000000;
    ANSELC = 0b10000000;

    ADON = 0b1;
    ADCON1 = 0b11010111;
    FVRCON = 0b11000010;
    /* END ANALOG */

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

/* Reset the ESC sending a pulse for 1ms */
void resetESC() {
    /* Reset ESC 1 */
    RC5 = ON;
    __delay_us(1000);
    RC5 = OFF;
    __delay_us(19000);
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

/* Sets the ESC with the correct signal. 
 * The signal lenght must be between 1ms to 2ms. */
void setESC1(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC1 = ON; /* Turn on RC5 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!TMR2IF); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC1 = OFF; /* Turn off RC5 */
    TMR2IF = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal. 
 * The signal lenght must be between 1ms to 2ms. */
void setESC2(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC2 = ON; /* Turn on RC5 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!TMR2IF); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC2 = OFF; /* Turn off RC5 */
    TMR2IF = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal. 
 * The signal lenght must be between 1ms to 2ms. */
void setESC3(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC3 = ON; /* Turn on RC5 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!TMR2IF); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC3 = OFF; /* Turn off RC5 */
    TMR2IF = FALSE; /* Reset the interrupt flag */
}

/* Sets the ESC with the correct signal. 
 * The signal lenght must be between 1ms to 2ms. */
void setESC4(char duration) {
    PR2 = duration; /* When TMR2 = PR2, TMR2IF is set */
    TMR2 = 0; /* Reset timer2 */
    RC4 = ON; /* Turn on RC5 */
    __delay_us(990);
    TMR2ON = TRUE; /* Turn on Timer 2 */
    while (!TMR2IF); /* Wait for interrupt */
    TMR2ON = FALSE; /* Turn off Timer 2 */
    RC4 = OFF; /* Turn off RC5 */
    TMR2IF = FALSE; /* Reset the interrupt flag */
}

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
