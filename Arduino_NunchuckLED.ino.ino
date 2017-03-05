/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012       by Tom Igoe
 modified again 3/4/2017   by Zia Mohammad

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A5;
const int analogInPin3 = A3;

const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutPin2 = 10;
const int analogOutPin3 = 11;

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;
int sensorValue3 = 0;

int outputValue = 0;        // value output to the PWM (analog out)
int outputValue2 = 0;
int outputValue3 = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  sensorValue2 = analogRead(analogInPin2);
  sensorValue3 = analogRead(analogInPin3);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);
  outputValue3 = map(sensorValue3, 0, 1, 0, 1);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);
  analogWrite(analogOutPin2, outputValue2);
  analogWrite(analogOutPin3, outputValue3);

  // print the results to the serial monitor:
  Serial.print("sensor UD = ");
  Serial.print(sensorValue);
  Serial.print("\t output UD = ");
  Serial.println(outputValue);

Serial.print("sensor LR = ");
  Serial.print(sensorValue2);
  Serial.print("\t output LR = ");
  Serial.println(outputValue2);

  Serial.print("button = ");
  Serial.print(sensorValue3);
  Serial.print("\t output button = ");
  Serial.println(outputValue3);
Serial.println();

  // wait 750 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(750);
}
