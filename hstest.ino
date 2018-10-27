#include "HapticSensor.h"
// Debugging switches and macros
#define DEBUG 1 // Switch debug output on and off by 1 or 0

#if DEBUG
#define PRINTS(s)   { Serial.print(F(s)); }
#define PRINT(s,v)  { Serial.print(F(s)); Serial.print(v); }
#else
#define PRINTS(s)
#define PRINT(s,v)
#endif
/****************************************************************************/


// precalculated values for P = Cos[omega*t]
const float HapticSensor::P[] = { 1.00, 0.92, 0.71, 0.38, 0.00, -0.38, -0.71, -0.92, -1.00, -0.92, -0.71, -0.38, 0.00, 0.38, 0.71, 0.92 };

// precalculated values for Q = Sin[omega*t]*Exp[t/tau]
const float HapticSensor::Q[] = { 0.00, 0.38, 0.71, 0.92, 1.00, 0.92, 0.71, 0.38, 0.00, -0.38, -0.71, -0.92, -1.00, -0.92, -0.71, -0.38 };

// wave decay factor
const float HapticSensor::k = 0.9;

// gamma factor - I play with this alot when changing hardware to tune in good effect
const float HapticSensor::gamma = 7.1;
// timer
long HapticSensor::lastUpdate = 0;
// force limit
const float HapticSensor::fMax = 1023.0;

// instantiate sensors on pin pairs read pin, pwm pin

HapticSensor tipSensor = HapticSensor(20, 6);
HapticSensor upperSensor = HapticSensor(15, 5);
HapticSensor lowerSensor = HapticSensor(14,10);
HapticSensor baseSensor = HapticSensor(21, 16);


// define the LED pin
#define LED 13



// helper function to specify standard out to serial for printf functionality
/*
 int my_putc(char c, FILE *t) {
  Serial.write(c);
}
 */

void setup() {
  #if DEBUG
  Serial.begin(9600);       // open serial port if DEBUG enabled
  #endif

  //fdevopen statement (with helper function my_putc) enables printf to serial
 // fdevopen(&my_putc, 0);

  tipSensor.begin();
  PRINTS("\ntipSensor begin\t.\t.\t.\t.\t.\t.\t.");
  upperSensor.begin();
  PRINTS("\nupperSensor begin\t.\t.\t.\t.\t.\t.\t.");
  lowerSensor.begin();
  PRINTS("\nlowerSensor begin\t.\t.\t.\t.\t.\t.\t.");
  baseSensor.begin();
  PRINTS("\nbaseSensor begin\t.\t.\t.\t.\t.\t.\t.");

  pinMode(LED, OUTPUT);
  PRINT("finished setup at millis:", millis());
//  delay(250);
}

void loop() {
	static long lastTime = 0;
	static int count = 0;
	const uint8_t deltat = 42;
	if (lastTime + deltat <= millis() ) {
	  PRINTS("\n tip ");
		tipSensor.update();
		PRINTS("\tupper ");
		upperSensor.update();
    PRINTS("\tlower ");
    lowerSensor.update();
  	PRINTS("\tbas ");
		baseSensor.update();
		lastTime = millis();
		count++;
	}
}

