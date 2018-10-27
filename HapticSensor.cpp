/************************************************************************/
/*  HapticSensor.cpp                                                    */
/*      by Jon A. Nuljon                                                */
/*    December 2017                                                     */
/************************************************************************/
#include "HapticSensor.h"
#include <CapacitiveSensor.h>


// CONSTRUCTOR: sense signal pin , PWM output pin
HapticSensor::HapticSensor(uint8_t receivePin, uint8_t pwmPin) : signalPin(receivePin), feedbackPin(pwmPin)
{
}

void HapticSensor::begin()
{
    capSensor.set_CS_AutocaL_Millis(0x2710); //set for 10 seconds calibration intervals
    pinMode(feedbackPin, OUTPUT);
}
// this is the private method
float HapticSensor::readSensor(float *sensorHistory)
{
    // shift history
    for (uint8_t m = 15; m > 0; m--)
    {
        sensorHistory[m] = sensorHistory[m - 1];
    }
    // read the sensor
    float sensed = capSensor.capacitiveSensor(25);
    if (sensed <= 13.0)
    {
        sensed = 0.0;
    }
    sensorHistory[0] = sensed;
    PRINT("\tCS: ", sensed);
    ;
    return sensed;
}

// this is the private method
int HapticSensor::feedbackSensor(float *sensorHistory, int vMax)
{
    float n = tau / deltat;
    float p = 0.0; //integrated cos power
    float q = 0.0; //integrated sin power
    for (uint8_t m = 0; m < 16; m++)
    {                                    //integrals
        p = p + P[m] * sensorHistory[m]; // p = sum of (Cos[omega*t] * sensor reading)
        q = q + Q[m] * sensorHistory[m]; // q = sum of (Sin[omega*t]*Exp[t/tau] * sensor reading)
    }
    float F = k * sqrt(p * p + q * q) / 16; // root Mean Square *90%
    PRINT("\tF: ", F);
    float temp = ((F * gamma - (float)vOld) / n);
    temp = temp + (float)vOld;
    //(long)temp;
    //PRINT("\tt: ", temp);
    //long vNew = map(temp, -30000L, 30000L, 0, vMax);
    float vNew = temp;
    //try casting to constrain vNew
    vNew = (uint8_t)vNew;
    // if  (vNew > vMax) vNew = vMax;
    //if (temp >vMax) vNew = vMax;
    if (vNew == 0)
    {
        digitalWrite(LED, 0); // turn off LED
    }
    else
    {
        digitalWrite(LED, 1); // turn on LED
    }
    if (vNew < vMax)
        spinHS(vNew);
    else
        spinHS(vMax);
    //feedbackSensor(temp);
    vOld = vNew;
    return vOld;
}
// this is the public method
float HapticSensor::readSensor()
{
    // read the sensor
    float sensed = capSensor.capacitiveSensor(25);
    if (sensed <= 13.0)
    {
        sensed = 0.0;
    }
    PRINT("\tCS: ", sensed);
    return sensed;
}
// this is the public method
void HapticSensor::feedbackSensor(int v)
{
    PRINTS("\n");
    int vMax = 255;
    // constrain(v, 0, vMax);
    if (v < vMax)
        spinHS(v);
    else
        spinHS(vMax);
}

// spin an individual Haptic Sensor at value V
void HapticSensor::spinHS(int v)
{
    analogWrite(feedbackPin, v);
    PRINT("v: ", v);
    PRINTS("\t|");
}

// the update controller
void HapticSensor::update()
{

    //PRINT("\tUpdate time: ", millis() - lastUpdate);
    float *ptrHistory = &sensorHistory[0];
    readSensor(ptrHistory);
    int vMax = 255;
    feedbackSensor(ptrHistory, vMax);
}

// stop pulsing motor
void HapticSensor::stopHS()
{
    analogWrite(feedbackPin, 0);
    PRINTS("\n^^^^^^^^^^^^^^^^^^^ resting");
}