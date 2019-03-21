// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
String strength;
String d;


bool b1 = false;
bool b2 = false;
bool b3 = false;
String b = "check b: ";

int lightPen1 = A0; //define a pin for Photo resistor of bottle 1
int lightPen2 = A1 ; //define a pin for Photo resistor of bottle 2
int lightPen3 = A2 ; //define a pin for Photo resistor of bottle 3
int full1 = analogRead(lightPen1); //sets initial condition for bottle 1
int full2 = analogRead(lightPen2); //sets initial condition for bottle 2
int full3 = analogRead(lightPen3); //sets initial condition for bottle 3


enum Drink {
  d1,
  d2,
  d3,
  strong,
  virgin,
  regular,
  sure,
  check,
  make
};

Drink drink = d1;

void setup() {
  // Debugging output
  Serial.begin(9600);
  analogReference(INTERNAL);
  lcd.begin(16, 2);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  lcd.print("Drink 1");

}

uint8_t i = 0;
void loop() {

  lcd.setCursor(0, 0);
  uint8_t buttons = lcd.readButtons();


  switch (drink) {
    case d1:
      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Drink 2 ");
        drink = d2;
      }
      else if (buttons & BUTTON_LEFT) {
        delay(500);
        lcd.print("Drink 3 ");
        drink = d3;
      }
      else if (buttons & BUTTON_SELECT) {
        digitalWrite(3, HIGH);
        lcd.setBacklight(RED);
        delay(500);
        lcd.print("Regular ");
        drink = regular;
        d = "d1";
        Serial.println(d);
        

      }
      break;

    case d2:

      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Drink 3 ");
        drink = d3;
      }
      else if (buttons & BUTTON_LEFT) {
        
        delay(500);
       
        lcd.print("Drink 1 ");
        drink = d1;
      }
      else if (buttons & BUTTON_SELECT) {
        lcd.setBacklight(GREEN);
        digitalWrite(7, HIGH);
        delay(500);
        
        lcd.print("Regular ");
        drink = regular;
        d = "d2";
        Serial.println(d);
      }
      break;

    case d3:
      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Drink 1 ");
        drink = d1;
      }
      else if (buttons & BUTTON_LEFT) {
        delay(500);
        lcd.print("Drink 2 ");
        drink = d2;
      }
      else if (buttons & BUTTON_SELECT) {
        digitalWrite(5, HIGH);
        lcd.setBacklight(YELLOW);
        delay(500);
        
        lcd.print("Regular ");
        drink = regular;
        d = "d3";
        Serial.println(d);

      }
      break;

    case regular:
      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Strong ");
        drink = strong;
      }
      else if (buttons & BUTTON_LEFT) {
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;
      }
      else if (buttons & BUTTON_SELECT) {
        delay(500);
        lcd.print("Are you sure: ");
        lcd.setCursor(0, 1);
        //call to drink function

        strength = "regular";
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);
        //call to drink function
        drink = sure;
      }
      else if (buttons & BUTTON_UP) {
        drink = d1;
        d = "";
        lcd.clear();
        lcd.print("Drink 1 ");
        lcd.setBacklight(WHITE);
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
        delay(500);
      }
      break;

    case strong:
      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;
      }
      else if (buttons & BUTTON_LEFT) {
        delay(500);
        lcd.print("Regular ");
        drink = regular;
      }
      else if (buttons & BUTTON_SELECT) {
        delay(500);
        lcd.print("Are you sure: ");
        drink = sure;

        strength = "strong";
        lcd.setCursor(0, 1);
        
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);
      

      }
      else if (buttons & BUTTON_UP) {
        drink = d1;
        d = "";
        lcd.clear();
        lcd.print("Drink 1 ");
        lcd.setBacklight(WHITE);
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
        delay(500);
      }
      break;

    case virgin:
      if (buttons & BUTTON_RIGHT) {
        delay(500);
        lcd.print("Regular ");
        drink = regular;
      }
      else if (buttons & BUTTON_LEFT) {
        delay(500);
        lcd.print("Strong ");
        drink = strong;
      }
      else if (buttons & BUTTON_SELECT) {
        delay(500);
        lcd.print("Are you sure: ");
        drink = sure;
        strength = "virgin";
        lcd.setCursor(0, 1);
        //call to drink function
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);

        //call to drink function

        //call to drink function

      }
      else if (buttons & BUTTON_UP) {
        drink = d1;
        d = "";
        lcd.clear();
        lcd.print("Drink 1 ");
        lcd.setBacklight(WHITE);
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
        delay(500);
      }
      break;

    case sure:
      if (buttons & BUTTON_SELECT) {
        delay(500);
        lcd.print("Making      ");

        Serial.print(d);
        Serial.print(" ");
        Serial.print(strength);
        drink = check;
      }
      else if (buttons & BUTTON_UP) {
        lcd.clear();
        drink = d1;
        d = "";
        strength = "";
        lcd.print("Drink 1 ");
        lcd.setBacklight(WHITE);
        digitalWrite(3, LOW);
        digitalWrite(5, LOW);
        digitalWrite(7, LOW);
        delay(500);
      }
      break;
    case check:
      b1 = check1();
      if (b1 == false) {
        b = b + "1 ";
      }
      b2 = check2();
      if (b2 == false) {
        b = b + "2 ";
      }
      b3 = check3();
      if (b3 == false) {
        b = b + "3 ";
      }
      if (b1 || b2 || b3) {
        lcd.print(b);
        break;
      }
      drink = make;
      break;
    case make:
      lcd.clear();
      lcd.print("making");
      //do work
      delay(5000);
      drink = d1;
      break;
  }
 
}




bool check1() {
  if (analogRead(lightPen1) < .8 * full1) { //Tests to see if bottle 1 is empty
    //lcd.print("Bottle 1 Empty");
    delay(10);
    return true;
  }
  return false;

}


bool check2() {
  if (analogRead(lightPen2) < .8 * full2) { // Test to see if bottle 2 is empty
    //lcd.print("Bottle 2 Empty");
    delay(10);
    return true;
  }
  return false;
}

bool check3() {
  if (analogRead(lightPen3) < .8 * full3) { // Tests to see if bottle 3 is empty
    //lcd.print("Bottle 3 Empty");
    delay(10);
    return true;
  }
  return false;
}
