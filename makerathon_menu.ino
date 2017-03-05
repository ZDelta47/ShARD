#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(4);
int row = 0;
int column;
int mode;
boolean input[4];
const int analogInPin = A1;  // Up Down
const int analogInPin2 = A2;  //Left Right
const int analogInPin3 = A0;  // button

const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutPin2 = 10;
const int analogOutPin3 = 11;

int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;
int sensorValue3 = 0;


boolean updown;
boolean button;
boolean leftright;
boolean neutral;
static const unsigned char PROGMEM pointerMap[] =
{
  B00000000,
  B11000000,
  B11110000,
  B11111110,
  B11111000,
  B11000000,
  B00000000,
  B00000000,
};
static const unsigned char PROGMEM EpointerMap[] =
{
  B00000000,
  B11000000,
  B10110000,
  B10001110,
  B10110000,
  B11000000,
  B00000000,
  B00000000,
};
void ifstatements() {

  if (sensorValue3 > 200) { //The button
    button = false; //Not pushed
  }

  if (sensorValue3 < 199) {
    button = true;   //Button Pushed
  }

  //-------------------------------------------------
  if (sensorValue2 <= 350 && sensorValue2 >= 330 && sensorValue <= 350 && sensorValue >= 330) {
    neutral = true;
  }

  else {
    neutral = false;
  }

  if (sensorValue2 >  350) {  //The Left Right
    leftright = false;      // Right Enable
  }

  if (sensorValue2 < 330) {
    leftright = true;      //Left Enable
  }

  //------------------------------------------------
  if (sensorValue > 350) {  //The Up Down
    updown = false;       //Up Enable
  }
  if (sensorValue < 330) {
    updown = true;        //Down Enable
  }
  input [1] = updown;
  input [2] = leftright;
  input [3] = button;
  input [0] = neutral;
}

void pinread() {
  // ---------------------------Controller Setup---------------------------------------
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  sensorValue2 = analogRead(analogInPin2);
  sensorValue3 = analogRead(analogInPin3);

  // map it to the range of the analog out:

}


void mainMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println("Main menu");
  display.setCursor(20, 8);
  display.println("ping-pong");
  display.setCursor(20, 16);
  display.println("Credit");
  display.setCursor(20, 24);
  display.println("Exit");
  display.display();
}
void pingPong() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println("Ready");
  display.setCursor(20, 8);
  display.println("Exit");
  display.display();
}
void Credit() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 0);
  display.println("Credit");
  display.setCursor(20, 8);
  display.println("Zaheer Hasan");
  display.setCursor(20, 16);
  display.println("Zia Mohammad");
  display.setCursor(20, 24);
  display.println("Hucheng Guo");
  display.setCursor(20, 80);
  display.println("Exit");
  display.display();
}
void pointer() {
  display.fillRect(0, 0, 8, 32, BLACK);
  display.drawBitmap(0, row * 8,  pointerMap, 8, 8, 1);
  display.display();
  delay(200);
}
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  Serial.begin(9600);
  mainMenu();
}
void loop() {
  pinread();
  ifstatements();
  Serial.println(" ");
  for (int i = 0; i < 4; i++){
    Serial.print(input[i]);
  }
  
  if (input[0] == 1) {
    delay(40);
  }
  else {
    if (input[1] == 1) {
      row++;
    }
    else {
      row--;
    }
    if (row > 3) {
      row = 1;
    }
    if (row < 1) {
      row = 3;
    }
  }
  pointer();
  if (input[3] == 1) {
    if (column == 0) {
      if (row == 3) {
        display.clearDisplay();
        column--;
      }
      else if (row == 1) {
        mode = 1;
        column++;
        pingPong();
      }
      else if (row == 2) {
        mode = 2;
        column++;
        Credit();
      }
    }
    else if (column == 1){
      if (mode == 2){
        column = 0;
        mainMenu();
      }
    }
    else if (column == -1){
      mainMenu();
      column = 0;
    }
  }
}



