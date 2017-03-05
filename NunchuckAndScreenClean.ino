/*
  Analog input, analog output, serial output

 
 created 29 Dec. 2008
 modified 9 Apr 2012       by Tom Igoe
 modified again 3/4/2017   by Zia Mohammad, Zaher Hasan, & Neo

 Some elements in the example code are in the public domain.

This includes an example for our Monochrome OLEDs based on SSD1306 drivers

Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98
This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution

 */
//   Parameters for the Controller:
// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A1;  // Up Down
const int analogInPin2 = A2;  //Left Right
const int analogInPin3 = A0;  // button

const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutPin2 = 10;
const int analogOutPin3 = 11;

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;
int sensorValue3 = 0;

int outputValue = 0;        // value output to the PWM (analog out)
int outputValue2 = 0;
int outputValue3 = 0;

boolean updown;
boolean button;
boolean leftright;
boolean neutral;



//-------------------------Main Code----------------------------------------------------
void ifstatements(){

  if (sensorValue3 > 200){  //The button
  button = false; //Not pushed
  }
  
  if (sensorValue3 < 199){
  button = true;   //Button Pushed
  }

  //-------------------------------------------------
  if (sensorValue2 <= 350 && sensorValue2 >= 330 && sensorValue <= 350 && sensorValue >= 330){
    neutral = true;
  }
  
  else{
    neutral = false;
  }

  if (sensorValue2 >  350){   //The Left Right
  leftright = false;      // Right Enable
  }
  
  if (sensorValue2 < 330){
  leftright = true;      //Left Enable
  }

  //------------------------------------------------
  if (sensorValue > 350){   //The Up Down
  updown = false;       //Up Enable
  }
  if (sensorValue < 330){
  updown = true;        //Down Enable
  }
  boolean input [4] = {updown, leftright, button, neutral};
}

void pinread() {
 // ---------------------------Controller Setup---------------------------------------
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
}

void setup() {
 Serial.begin(9600);
}

void loop() {
  pinread();
  ifstatements();
}
