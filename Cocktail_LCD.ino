// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  8
#define CLK  9

HX711 scale;
// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();// intializes state machine

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

String strength;//state machine
String d;//Stores drink choice
String pDrink; // stores last drink

float w1 = 2;//The predetermind weights
float w2 = 3;
float w3 = 5;

bool b1 = false;// checks each bootle
bool b2 = false;
bool b3 = false;
String b = "check b: ";

int lightPen1 = A0; //define a pin for Photo resistor of bottle 1
int lightPen2 = A1 ; //define a pin for Photo resistor of bottle 2
int lightPen3 = A2 ; //define a pin for Photo resistor of bottle 3
int full1 = analogRead(lightPen1); //sets initial condition for bottle 1
int full2 = analogRead(lightPen2); //sets initial condition for bottle 2
int full3 = analogRead(lightPen3); //sets initial condition for bottle 3


enum Drink { // state machine
  d1,// Highlights drink 1 on the menu
  d2,// Highlights drink 2 on the menu
  d3,// Highlights drink 3 on the menu
  setI1,//Change bottle to new I1
  setI2,//Change bottle to I2
  setI3,//Change bottle to I2
  strong,//Highlights strong on the menu
  virgin,//Highlights virgin on the menu
  regular,//Highlights Regular on the menu
  sure,//Makes sure the right drink and strength was selected
  check,//Checks the supplies in the 3 bottles
  m1,//runs the first motor
  m2,//runs the second motor
  m3//runs the third motor
};

Drink drink = d1; // sets state machine to drink 1 at the begining

void setup() {
  // Debugging output
  Serial.begin(9600);// begins serial

  scale.begin(DOUT, CLK);//intialize scale
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  analogReference(INTERNAL);//sets the reference to internal

  lcd.begin(16, 2); //iniaitalizes LCD
  lcd.print("Drink 1");// sends first message for first state

}

uint8_t i = 0;//sets number for buttons = 0
void loop() {

  lcd.setCursor(0, 0);//set LCD to first row
  uint8_t buttons = lcd.readButtons();//reads buttons for

  switch (drink) {//State Machine
    case d1:
      if (buttons & BUTTON_RIGHT) {//swtiches to Drink 2
        delay(500);
        lcd.print("Drink 2 ");//prints new state on LCD
        drink = d2;//sets state to drink 2
      }
      else if (buttons & BUTTON_LEFT) {//swtiches Drink 3
        delay(500);
        lcd.print("Drink 3 ");//prints new state on LCD
        drink = d3;//sets state to drink 3
      }
      else if (buttons & BUTTON_SELECT) {//swtiches to check ingredents
        lcd.setBacklight(RED);//sets the lcd backround
        delay(500);
        drink = setI1;//changes state to checking if the right ingredients are hooked up
        d = "d1";//sets drink to drink 1
      }
      break;

    case d2:

      if (buttons & BUTTON_RIGHT) {//swtiches to drink 3
        delay(500);
        lcd.print("Drink 3 ");//prints new state on LCD
        drink = d3;//sets state to drink 3
      }
      else if (buttons & BUTTON_LEFT) {//swtiches to drink 1
        delay(500);
        lcd.print("Drink 1 ");//prints drink 1 on LCD
        drink = d1;//sets state to drink 1
      }
      else if (buttons & BUTTON_SELECT) {//swtiches state
        lcd.setBacklight(GREEN);//sets LCD backround
        delay(500);
        drink = setI1;// Swtiches to check supplies
        d = "d2";// stes drink to drink 2
      }
      break;

    case d3:
      if (buttons & BUTTON_RIGHT) {//switches to Drink 1
        delay(500);
        lcd.print("Drink 1 ");//pirnts new state on LCD
        drink = d1;//sets state to drink 1
      }
      else if (buttons & BUTTON_LEFT) {//switches to Drink 2
        delay(500);
        lcd.print("Drink 2 ");//prints
        drink = d2;
      }
      else if (buttons & BUTTON_SELECT) {//Change ingredents
        lcd.setBacklight(YELLOW);
        delay(500);
        lcd.print("Regular ");
        drink = setI1;// Checks supply change
        d = "d3";//sets drink to d3
      }
      break;


    case setI1:
      if (d == pDrink) {// Drinks are the same as the previous so nothing happens
        d = regular;
        lcd.print("Regular     ");
        break;
      }//else the drinks differ and the supplies need to be switched
      else if (d == "d1") {// If it is drink 1
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {//once user changes I1
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;//sets state to check next bottle
          break;
        }
      }
      else if (d == "d2") {//if it is drink 2
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {//once user changes I1
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;//sets state to check next bottle
          break;
        }
      }
      else if (d == "d3") {
        if it is drink 3
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {//once user changes I1
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;//sets state to check next bottle
          break;
        }
      }

    case setI2:
      if (d == "d1") {
        if (buttons & BUTTON_SELECT) {//once user changes I2
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;//sets state to check next bottle
          break;
        }
      }
      else if (d == "d2") {
        if (buttons & BUTTON_SELECT) {//once user changes I2
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;//sets state to check next bottle
          break;
        }
      }
      else if (d == "d3") {
        if (buttons & BUTTON_SELECT) {//once user changes I2
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;//sets state to check next bottle
          break;
        }
      }


    case setI3: //After this state, the drinks switch

      if (buttons & BUTTON_SELECT) {//once user changes I3
        delay(500);
        lcd.print("Regular    ");//Prints new State
        drink = regular;//sets state to regular
        break;
      }

    case regular:
      if (buttons & BUTTON_RIGHT) {//switches state to strong
        delay(500);
        lcd.print("Strong ");
        drink = strong;
      }
      else if (buttons & BUTTON_LEFT) {//switched state to virgin
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;
      }
      else if (buttons & BUTTON_SELECT) {//Strength seleceted
        delay(500);
        lcd.print("Are you sure: ");
        lcd.setCursor(0, 1);//Prints the drink choice
        strength = "regular";
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);
        drink = sure;//Sets state to make sure the right drink was selected
      }
      else if (buttons & BUTTON_UP) {//return to start
        drink = d1;//sets staste back to begining
        d = "";//empties value
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
      if (buttons & BUTTON_RIGHT) {//sets state to vrigin
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;
      }
      else if (buttons & BUTTON_LEFT) {// sets state to regular
        delay(500);
        lcd.print("Regular ");
        drink = regular;
      }
      else if (buttons & BUTTON_SELECT) {//Strength seleceted
        delay(500);
        lcd.print("Are you sure: ");//
        drink = sure;//sets state to sure
        strength = "strong";
        lcd.setCursor(0, 1);//Prints out selection
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);
      }
      else if (buttons & BUTTON_UP) {//return to start
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
      if (buttons & BUTTON_RIGHT) {//sets state to regular
        delay(500);
        lcd.print("Regular ");
        drink = regular;
      }
      else if (buttons & BUTTON_LEFT) {//sets state to strong
        delay(500);
        lcd.print("Strong ");
        drink = strong;
      }
      else if (buttons & BUTTON_SELECT) {//Strength selected
        delay(500);
        lcd.print("Are you sure: ");
        drink = sure;//sets state to sure
        strength = "virgin";//prints out drink sleection
        lcd.setCursor(0, 1);
        lcd.print(d);
        lcd.print(" ");
        lcd.print(strength);

      }
      else if (buttons & BUTTON_UP) {//return to start
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
      if (buttons & BUTTON_SELECT) { //Checks if right selection was made
        delay(500);
        lcd.print("Making      ");//Prints on LCD
        pDrink = d;//sets prevouis drink
        drink = check;//sets state to check how much liquid is remaining
      }
      else if (buttons & BUTTON_UP) {//return to start
        lcd.clear();
        drink = d1;//sets state back to begining
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
    case check://Checkes the levels of each bottles
      b1 = check1();
      if (b1 == false) {//if b1 is empty
        b = b + "1 ";
      }
      b2 = check2();
      if (b2 == false) {//if b2 is empty
        b = b + "2 ";
      }
      b3 = check3();
      if (b3 == false) {//if b3 is empty
        b = b + "3 ";
      }
      if (b1 || b2 || b3) { // if a bottle is empty
        lcd.print(b);
        break;
      }
      drink = m1;//if full then make starts
      break;

    case m1:
      lcd.clear();
      lcd.print("making");//starts the drink making process

      drink = m2; // switches motors

      break;

    case m2:


      drink = m3;// switches motors

      break;

    case m3:

      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start

      break;
  }

}


// helper methods

bool check1() {
  if (analogRead(lightPen1) < .8 * full1) { //Tests to see if bottle 1 is empty
    delay(10);
    return true;
  }
  return false;

}


bool check2() {
  if (analogRead(lightPen2) < .8 * full2) { // Test to see if bottle 2 is empty
    delay(10);
    return true;
  }
  return false;
}

bool check3() {
  if (analogRead(lightPen3) < .8 * full3) { // Tests to see if bottle 3 is empty
    delay(10);
    return true;
  }
  return false;
}

//bool weight(float w) {//returns true if the weight is >= when it needs to switch
//  Serial.print("Reading: ");
//  float r = scale.get_units(); //scale.get_units() returns a float
//  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
//  Serial.println();
//  if (w >= r) {
//    return true;
//  }
//  return false;
//
//}
