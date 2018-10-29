#ifndef _HAPTICSENSOR_h
#define _HAPTICSENSOR_h
#endif // !_HAPTICSENShR_H
#include <stdint.h>
#include <CapacitiveSensor.h>


/****************************************************************************/
/*  HapticSensor.h                                                          */
/*    Class interprets touch sensation as vibration (for a prosthetic?)     */
/*    Input from a capacitive sensor is processed using a mathematical      */
/*    model of a decaying waveform to signal a small motor or piezo. The	*/
/*	  generated signal simulates the experience of natural sensation.       */
/*    The feedback level corresponds to pressure of the touch, lingers a    */
/*    moment and then quickly tails off. The math comes from an open source */
/*    project run by a physics and math scientist calling himself Dr. O.    */
/*    The original software ran one gas pressure sensor and a novelty type  */
/*    vibrator. I began adapting the softwre to support arrays of sensors   */
/*    and corresponding feedback devices. Since then, the original project  */
/*    has dissappeared. Wishing to explore brain/body awarenes, I continue  */
/*    on experimental work pairing differing sensors with haptic response   */
/*    devices and have been iterating designs and software since 2015. This */
/*    version shows promise and so I share it in hopes others may find it   */
/*    and perhaps advance the concept, give me feedback for better math, or */
/*	  perhaps start a collaboration effort.                                 */
/*    copyright December 2017   by Jon A. Nuljon, nuljon.com                */
/*   licensed with GNU LGPLv3 https://choosealicense.com/licenses/lgpl-3.0/ */
/****************************************************************************/

class HapticSensor
{
    // private interface
  private:
    /******************* CLASS VARIABLES ****************************************/
    // supply_pin names the pin that all the capSensor objects share for voltage
    static const uint8_t supply_pin = 19;
    // P is an array that holds the wave component values P = Cos[omega*t]
    static const float P[16];
    // Q is an an that array holds the wave component values Q = Sin[omega*t]*Exp[t/tau]
    static const float Q[16];
    // tau is the wavelength period in milliseconds
    static const int tau = 666;
    // deltat sets the duration in milliseconds between sensor reads
    static const uint8_t deltat = 84;
    // k sets the wave decay factor
    static const float k;
    // fMax is the feedback maximum force limiter
    static const float fMax;
    // gamma is an amplification factor to tune the haptic feedback signal
    static const float gamma;
    // lastUpdate is register to keep time
    static long lastUpdate;
    static const uint8_t LED = 13;

    /******************* INSTANCE  VARIABLES / methods***************************/
    // signalPin is where the capSensor object will receive the sensation signals.
    const uint8_t signal_pin_;
    // feedbackPin is where the feedback is transmitted (PWM capable pin).
    const uint8_t feedbackPin;
    // capSensor is an instance of the CapacitiveSensor class (library)- requires passing 2 pin values.
    CapacitiveSensor capSensor = CapacitiveSensor(supply_pin, signal_pin_);
    // vOld tracks the last haptic response level.
    int vOld = 0;
    // readSensor() captures the sensation signal. It requires passing a pointer to sensorHistory.
    float readSensor(float *sensor_history);
    // It requires passing a  and the .
	/**
     * \feedbackSensor() returns the haptic response value. 
     * \param sensor_history 
     * \param vMax maximum feedback value limit
     * \return the feedback response value
     */
    int feedbackSensor(float *sensorHistory, int vMax = 250);
    // 
	/**
     * \spinHS() transmits the feedback response. 
     * \param v  feedback response value.
     */
    void spin_hs(int v);
    
	/**
     * \sensorHistory stores the last 16 sensation signals.
     */
    float sensorHistory[16] = {0.0};

    // PUBLIC INTERFACE

  public:
    // To construct a HapticSensor object requires passing the pin
    // that will receive the signal from the capacitive sensor
    // circuit and the pin that will transmit the haptic feedback
    // response via a Pulsed Width Modulated (PWM) signal
    HapticSensor(uint8_t receivePin, uint8_t pwmPin);

    // begin() activates the capSensors. call from setup
    void begin(void);

    // update() controls sensor readings and haptic responses. call from loop
    void update(void);

    // readSensor() returns a sensor reading outside of update process - hardware test
    float readSensor();

    // feedbackSensor(value) manually transmit feedback equal to value - hardware test
    void feedbackSensor(int v);

    // stopHS() stops the feedback response immidiately
    void stopHS(void);

};
