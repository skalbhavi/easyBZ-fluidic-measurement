

/*
 * adc_test.c
 * 
 * adc.h example.
 * 
 * Author:      Sebastian Goessl
 * Hardware:    ATmega328P
 * 
 * LICENSE:
 * MIT License
 * 
 * Copyright (c) 2018 Sebastian Goessl
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */



#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#if 0
#include <adc.h>
#include <uart.h>

void my_init(void);
void my_init(void) {

}

// the setup function runs once when you press reset or power the board
void setup() {
  my_init();
  adc_init();
  uart_init();
  sei();
}

// the loop function runs over and over again forever
void loop() {
    size_t i;
  //int i;
    uint16_t value_0 = 0, avg_value_0 = 0, value_1 = 0;
    int numReadings = 10, channel_offset=0;
    uint16_t channels[ADC_N];
    
    
#if 0
    for(i=0; i<ADC_N-1; i++)
        printf("%4d, ", channels[i]);
    printf("%4d\n", channels[ADC_N-1]);
#endif

for (i = 0; i < numReadings; i++){
    // Read light sensor data.
    adc_getAll(channels);
    value_0 = value_0 + (channels[0] - channel_offset);
    //value_1 = value_1 + channels[1];
    // 1ms pause adds more stability between reads.
    _delay_ms(50);
  }
  // Take an average of all the readings.
  avg_value_0 = value_0 / numReadings;
  //value_1 = value_1 / numReadings;
  //printf("%4d\n", channels[0]);
  printf("%4d\n", avg_value_0);
  
  //printf("%4d, %4d\n", value_0, value_1);
  _delay_ms(10);
}
#endif

#if 0
#include <smoothadc.h>
SmoothADC		ADC_0;				// SmoothADC instance for Pin 0
SmoothADC		ADC_1;				// SmoothADC instance for Pin 1
unsigned int	ADC0Value = 0;		// ADC0 final value
unsigned int	ADC1Value = 0;		// ADC1 final value

unsigned int	MemTimeSerial;

void setup()
{
	Serial.begin(9600);

	ADC_0.init(A0, TB_US, 500);	// Init ADC0 attached to A0 with a 500us acquisition period
//	ADC_0.init(A0, TB_MS, 50);	// Init ADC1 attached to A1 with a 50ms acquisition period
	if (ADC_0.isDisabled())	{ ADC_0.enable(); }
//	ADC_1.init(A1, TB_MS, 50);	// Init ADC1 attached to A1 with a 50ms acquisition period
//	if (ADC_1.isDisabled())	{ ADC_1.enable(); }
}

void loop()
{
	unsigned int	tempTime = millis();
	String			toSerial = "";
	int i;
  int value_0 = 0, value_1 = 0;
  int numReadings = 60;
  int avgValue = 0, ADC_Total_Value = 0;
	ADC_0.serviceADCPin();
//	ADC_1.serviceADCPin();
	
//	if ((tempTime - MemTimeSerial) > 1000)
//	{
//		MemTimeSerial = tempTime;
		
		#ifdef DEBUG
		ADC_0.dbgInfo();
	//	ADC_1.dbgInfo();
		#endif
	for (i = 0; i < numReadings; i++) {
		ADC0Value = ADC_0.getADCVal();
	//	ADC1Value = ADC_1.getADCVal();
		
	//	toSerial += "ADC Channel 0:\t";
		//toSerial += ADC0Value;
    ADC_Total_Value += ADC0Value;
    
	//	toSerial += "\tADC Channel 1:\t";
	//	toSerial += ADC1Value;
	//	Serial.println(toSerial);
	}
  avgValue = ADC_Total_Value / numReadings;
  toSerial += avgValue;
  toSerial += ", ";
  Serial.println(toSerial);
}
#endif


#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(9600);
 // Serial.println("HX711 Demo");

 // Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  //Serial.println("Before setting up the scale:");
  //Serial.print("read: \t\t");
  //Serial.println(scale.read());			// print a raw reading from the ADC

  //Serial.print("read average: \t\t");
  //Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

 // Serial.print("get value: \t\t");
 // Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

 // Serial.print("get units: \t\t");
 // Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  //Serial.println("After setting up the scale:");

  //Serial.print("read: \t\t");
//  Serial.println(scale.read());                 // print a raw reading from the ADC

  //Serial.print("read average: \t\t");
//  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  //Serial.print("get value: \t\t");
//  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  //Serial.print("get units: \t\t");
//  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  //Serial.println("Readings:");
}

#if 0
void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
#endif
void loop() {
  //Serial.print("read average: \t\t");
  //Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  //Serial.print("get value: \t\t");
  //Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  //Serial.print("get units: \t\t");
  //Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided

  //scale.power_down();			        // put the ADC in sleep mode
  //delay(5000);
  //scale.power_up();
  Serial.println(scale.read_average(5));  	// print the average of 20 readings from the ADC
  _delay_ms(1);
}