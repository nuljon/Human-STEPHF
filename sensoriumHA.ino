#define DEBUG 1 // Switch debug output on and off by 1 or 0
#if DEBUG
#define PRINTS(s)   { Serial.print(F(s)); }
#define PRINT(s,v)  { Serial.print(F(s)); Serial.print(v); }
#else
#define PRINTS(s)
#define PRINT(s,v)
#endif
#include "HapticSensor.h"
// Debugging switches and macros

//precalculated values for P = Cos[omega*t]
const float HapticSensor::P[] = { 1.00, 0.92, 0.71, 0.38, 0.00, -0.38, -0.71, -0.92, -1.00, -0.92, -0.71, -0.38, 0.00, 0.38, 0.71, 0.92 };

// precalculated values for Q = Sin[omega*t]*Exp[t/tau]
const float HapticSensor::Q[] = { 0.00, 0.38, 0.71, 0.92, 1.00, 0.92, 0.71, 0.38, 0.00, -0.38, -0.71, -0.92, -1.00, -0.92, -0.71, -0.38 };

// wave decay factor
const float HapticSensor::k = 0.9;

// gamma - adjust to tune new hardware
const float HapticSensor::gamma = 7.1;
// lastUpdate is a time register
long HapticSensor::lastUpdate = 0;
// force limit
const float HapticSensor::fMax = 1023.0;

// instantiate sensors on pin pairs read pin, pwm pin

HapticSensor hs1 = HapticSensor(13, 9);
HapticSensor hs2 = HapticSensor(15, 5);
HapticSensor hs3 = HapticSensor(14, 6);
HapticSensor hs4 = HapticSensor(16, 3);


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
  Serial.begin(115000);       // open serial port if DEBUG enabled
  #endif

  //fdevopen statement (with helper function my_putc) enables printf to serial
 // fdevopen(&my_putc, 0);

  hs1.begin();
  hs2.begin();
  hs3.begin();
  hs4.begin();

  pinMode(LED, OUTPUT);
  PRINT("finished setup at millis:", millis());
//  delay(250);
}

void loop() {
	static long lastTime = 0;
	static int count = 0;
	const uint8_t deltat = 42;
	if (lastTime + deltat <= millis() ) {
	  PRINTS("\nhs1 ");
      hs1.update();
      PRINTS("\ths2 ");
	  hs2.update();
      PRINTS("\ths3 ");
      hs3.update();
  	  PRINTS("\ths4 ");
	  hs4.update();
	  lastTime = millis();
	  count++;
	}
}
