// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include "HX711.h"

#define calibration_factor
#define Vodka 3                 // (pump1)12VDC motor to pump vodka on pin 3
#define Gingerale 4             // (pump2) Gingerale connected to pin 4
#define CranMango 5             // (pump3) CranMango on pin 5
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

String strength;//stores drink strength
String d;//Stores drink choice


bool b1 = false;// This Checks to see if bottle 1 is empty
bool b2 = false; // This checks to see if bottle 2 is empty
bool b3 = false;// This checks to see if bottle 3 is empty
String b = "check b: ";//Tells which bottle is empty if any

int lightPen1 = A0; //define a pin for Photo resistor of bottle 1
int lightPen2 = A1 ; //define a pin for Photo resistor of bottle 2
int lightPen3 = A2 ; //define a pin for Photo resistor of bottle 3
int full1 = analogRead(lightPen1); //sets initial condition for bottle 1
int full2 = analogRead(lightPen2); //sets initial condition for bottle 2
int full3 = analogRead(lightPen3); //sets initial condition for bottle 3


enum Drink { // What the screen highlights
  make,
  set,
  d1,//  drink 1 on the menu
  d2,//  drink 2 on the menu
  d3,//  drink 3 on the menu
//   setI1,//Change bottle to new I1
//   setI2,//Change bottle to I2
//   setI3,//Change bottle to I3
  strong,// strong on the menu
  virgin,//virgin on the menu
  regular,//Regular on the menu
  sure,//Makes sure the right drink and strength was selected
  check,//Checks the supplies in the 3 bottles
drinkmaking //Moves the process to drink making
};

Drink drink = set; // starts selection process at drink 1

void setup() {
  pinMode(Vodka, OUTPUT);

pinMode(Gingerale, OUTPUT);

pinMode(CranMango, OUTPUT);

digitalWrite (Vodka, HIGH);                                           //pump 1 off

digitalWrite (Gingerale, HIGH);                                       //pump 2 off

digitalWrite (CranMango, HIGH);                                       //pump 3 off

delay(1000);                                                          // let relays settle down before running the first time.
  // Debugging output
  Serial.begin(9600);// Starts the code

  scale.begin(DOUT, CLK);//intialize scale
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  analogReference(INTERNAL);//sets the reference to internal

  lcd.begin(16, 2); //iniaitalizes LCD
  lcd.print("Set Up");// sends first message for first state

}

uint8_t i = 0;//sets number for buttons = 0
void loop() {

  lcd.setCursor(0, 0);//set LCD to first row
  uint8_t buttons = lcd.readButtons();//reads buttons that have been selected

  switch (drink) {//Selction of drink
  case set: 
  if (buttons & BUTTON_SELECT) {
    delay(500);
    lcd.print("set alc to b1");
    while(!(buttons & BUTTON_SELECT)){
      
    }
    delay(500);
    lcd.print("set mix to b2");
    while(!(buttons & BUTTON_SELECT)){
      
    }
    lcd.print("set mix to b3");
    delay(500);
    while(!(buttons & BUTTON_SELECT)){
      
    }
    drink = d1;
    lcd.print("d1");
  }
  if(buttons & BUTTON_RIGHT||buttons & BUTTON_RIGHT){
    delay(500);
    lcd.print("make a drink");
    drink = make;
  }
  break;

    case make:
if (buttons & BUTTON_SELECT) {
  delay(500);
    drink = d1;
    lcd.print("d1");
  }
  if(buttons & BUTTON_RIGHT||buttons & BUTTON_RIGHT){
    delay(500);
    lcd.print("set up");
    drink = set;
  }
  break;

    case d1: // Places to go from drink 1
      if (buttons & BUTTON_RIGHT) {//switches to Drink 2
        delay(500);
        lcd.print("Drink 2 ");//prints drink 2 on LCD
        drink = d2;//highlights drink 2
      }
      else if (buttons & BUTTON_LEFT) {//switches to Drink 3
        delay(500);
        lcd.print("Drink 3 ");//prints Drink 3 on LCD Screen
        drink = d3;//highlight drink 2 
      }
      else if (buttons & BUTTON_SELECT) {//switches ingredients if needed
        lcd.setBacklight(RED);//sets the lcd backround
        delay(500);
        drink = regular;//moves the selction process to drink strength.
        d = "d1";//sets drink to drink 1
      }
      break;

    case d2: //Places to go from drink 2

      if (buttons & BUTTON_RIGHT) {//switches to drink 3
        delay(500);
        lcd.print("Drink 3 ");//prints Drink 3 on LCD
        drink = d3;//highlights drink 3
      }
      else if (buttons & BUTTON_LEFT) {//switches to drink 1
        delay(500);
        lcd.print("Drink 1 ");//prints drink 1 on LCD
        drink = d1;//highlights drink 1
      }
      else if (buttons & BUTTON_SELECT) {//Selects drink 2 and moves on to next menu
        lcd.setBacklight(GREEN);//sets LCD backround
        delay(500);
        drink = regular;// moves the selection process to drink strength 
        d = "d2";// sets drink to drink 2
      }
      break;

    case d3: // Places to go from drink 3
      if (buttons & BUTTON_RIGHT) {//switches to Drink 1
        delay(500);
        lcd.print("Drink 1 ");//prints Drink 1 on LCD
        drink = d1;//Highlights drink 1
      }
      else if (buttons & BUTTON_LEFT) {//switches to Drink 2
        delay(500);
        lcd.print("Drink 2 ");//prints drink 2 on LCD
        drink = d2;// highlights Drink 2
      }
      else if (buttons & BUTTON_SELECT) {//Selects drink 3 and moves on to next menu
        lcd.setBacklight(YELLOW);
        delay(500);
        lcd.print("Regular ");
        drink = regular;// highlights regular and moves to next selection process
        d = "d3";//sets drink to d3
      }
      break;


//     case setI1:
//       if (d == pDrink) {// Drinks are the same as the previous so nothing happens
//         d = regular;
//         lcd.print("Regular     ");
//         break;
//       }//else the drinks differ and the supplies need to be switched
//       else if (d == "d1") {// If it is drink 1
//         lcd.print("i1 to bottle1");
//         if (buttons & BUTTON_SELECT) {//once user changes I1
//           delay(500);
//           lcd.print("i2 to bottle2");
//           drink = setI2;//sets state to check next bottle
//           break;
//         }
//       }
//       else if (d == "d2") {//if it is drink 2
//         lcd.print("i1 to bottle1");
//         if (buttons & BUTTON_SELECT) {//once user changes I1
//           delay(500);
//           lcd.print("i2 to bottle2");
//           drink = setI2;//sets state to check next bottle
//           break;
//         }
//       }
//       else if (d == "d3") {
//         if it is drink 3
//         lcd.print("i1 to bottle1");
//         if (buttons & BUTTON_SELECT) {//once user changes I1
//           delay(500);
//           lcd.print("i2 to bottle2");
//           drink = setI2;//sets state to check next bottle
//           break;
//         }
//       }

//     case setI2:
//       if (d == "d1") {
//         if (buttons & BUTTON_SELECT) {//once user changes I2
//           delay(500);
//           lcd.print("i3 to bottle3");
//           drink = setI3;//sets state to check next bottle
//           break;
//         }
//       }
//       else if (d == "d2") {
//         if (buttons & BUTTON_SELECT) {//once user changes I2
//           delay(500);
//           lcd.print("i3 to bottle3");
//           drink = setI3;//sets state to check next bottle
//           break;
//         }
//       }
//       else if (d == "d3") {
//         if (buttons & BUTTON_SELECT) {//once user changes I2
//           delay(500);
//           lcd.print("i3 to bottle3");
//           drink = setI3;//sets state to check next bottle
//           break;
//         }
//       }


//     case setI3: //After this state, the drinks switch

//       if (buttons & BUTTON_SELECT) {//once user changes I3
//         delay(500);
//         lcd.print("Regular    ");//Prints new State
//         drink = regular;//sets state to regular
//         break;
//       }

    case regular://Selction choices from regular
      if (buttons & BUTTON_RIGHT) {//switches state to strong
        delay(500);
        lcd.print("Strong ");
        drink = strong;// highlights strong
      }
      else if (buttons & BUTTON_LEFT) {//switched state to virgin
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;// highlights virgin
      }
      else if (buttons & BUTTON_SELECT) {// regular strength is selected
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
      if (buttons & BUTTON_RIGHT) {//moves menu to  virgin
        delay(500);
        lcd.print("Virgin ");
        drink = virgin;//highlights virgin
      }
      else if (buttons & BUTTON_LEFT) {// moves menu to regular
        delay(500);
        lcd.print("Regular ");
        drink = regular;//highlights regular
      }
      else if (buttons & BUTTON_SELECT) {//Strong strength is selected
        delay(500);
        lcd.print("Are you sure: ");//
        drink = sure;//highlights sure
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
      if (buttons & BUTTON_RIGHT) {//moves menu to regular
        delay(500);
        lcd.print("Regular ");
        drink = regular;//highlights regular
      }
      else if (buttons & BUTTON_LEFT) {//moves menu to strong
        delay(500);
        lcd.print("Strong ");
        drink = strong;//highlights strong
      }
      else if (buttons & BUTTON_SELECT) {//Virgin strength is selected
        delay(500);
        lcd.print("Are you sure: ");
        drink = sure;//highlights sure
        strength = "virgin";//stores drink sleection
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
        lcd.print("Making"+d+strength);//Prints on LCD
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
      drink = drinkmaking;//if full then make starts
      break;

    case drinkmaking:
      lcd.clear();
      lcd.print("making");//starts the drink making process

                                                                      //Vodka Gingerale Strong
if (d=="d1" && strength=="strong"){
  while (scale.get_units()<75){
    digitalWrite (Vodka, LOW);                                        //pump 1 on
  }
  digitalWrite (Vodka, HIGH);                                         // Turns pump 1 off
  while(scale.get_units()<331 && scale.get_units()>=74){
  digitalWrite (Gingerale, LOW);                                      //pump 2 on
  }
  digitalWrite(Gingerale, HIGH);                                      // Pump 2 off
}
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
//////////////////////////////////////////////////////////////////
                                                                      //Vodka Gingerale Regular
if (d=="d1" && strength=="regular"){
  while (scale.get_units()<41){
    digitalWrite (Vodka, LOW);                                        //pump 1 on
  }
  digitalWrite (Vodka, HIGH);                                         // Turns pump 1 off
  while(scale.get_units()<331 && scale.get_units()>=40){
  digitalWrite (Gingerale, LOW);                                      //pump 2 on
  }
  digitalWrite(Gingerale, HIGH);                                      // Pump 2 off
}  
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
///////////////////////////////////////////////////////////////////
                                                                      //Vodka Gingerale virgin
if (d=="d1" && strength=="virgin"){
  while(scale.get_units()<331){
  digitalWrite (Gingerale, LOW);                                      //pump 2 on
  }
  digitalWrite(Gingerale, HIGH);                                      // Pump 2 off
}
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
/////////////////////////////////////////////////////////////////////
                                                                     //Vodka CranMango Strong
if (d=="d2" && strength=="strong"){
  while (scale.get_units()<75){
    digitalWrite (Vodka, LOW);                                       //pump 1 on
  }
  digitalWrite (Vodka, HIGH);                                        // Turns pump 1 off
  while(scale.get_units()<331 && scale.get_units()>=74){
  digitalWrite (CranMango, LOW);                                     //pump 3 on
  }
  digitalWrite(CranMango, HIGH);                                     // Pump 3 off
}
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
///////////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango regular
if (d=="d2" && strength=="regular"){
  while (scale.get_units()<41){
    digitalWrite (Vodka, LOW);                                        //pump 1 on
  }
  digitalWrite (Vodka, HIGH);                                         // Turns pump 1 off
  while(scale.get_units()<331 && scale.get_units()>=40){
  digitalWrite (CranMango, LOW);                                      //pump 3 on
  }
  digitalWrite(CranMango, HIGH);                                      // Pump 3 off
}
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
/////////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango Virgin
if (d=="d2" && strength=="virgin"){
    while(scale.get_units()<331){
  digitalWrite (CranMango, LOW);                                      //pump 3 on
  }
  digitalWrite(CranMango, HIGH);                                      // Pump 3 off
}
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango Gingerale Strong
if (d="d3" && strength=="strong"){
    while (scale.get_units()<75){
    digitalWrite (Vodka, LOW);                                        // pump 1 on
  }
  digitalWrite(Vodka, HIGH);                                          //pump 1 off
    while (scale.get_units()<202 && scale.get_units()>=74){
    digitalWrite (CranMango, LOW);                                    //pump 3 on
  }
  digitalWrite (CranMango, LOW);                                      //pump 3 off
    while (scale.get_units()<331 && scale.get_units()>=201){
      digitalWrite (Vodka, LOW);                                      //turns pump 2 on
  }
  digitalWrite(Vodka, HIGH);                                          //turns pump 2 off
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
/////////////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango Gingerale regular
if (d=="d3" && strength=="regular"){
    while (scale.get_units()<41){
    digitalWrite (Vodka, LOW);                                        // pump 1 on
  }
  digitalWrite(Vodka, HIGH);                                          //pump 1 off
    while (scale.get_units()<186 && scale.get_units()>=40){
    digitalWrite (CranMango, LOW);                                    //pump 3 on
  }
  digitalWrite (CranMango, LOW);                                      //pump 3 off
    while (scale.get_units()<331 && scale.get_units()>=185){
      digitalWrite (Gingerale, LOW);                                  //turns pump 2 on
  }
  digitalWrite(Gingerale, HIGH);                                      //turns pump 2 off
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
///////////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango Gingerale virgin
if (d=="d3" && strentgh=="virgin"){
      while (scale.get_units()<166){
    digitalWrite (CranMango, LOW);                                    // pump 3 on
  }
  digitalWrite(CranMango, HIGH);                                      //pump 3 off
    while (scale.get_units()<331 && scale.get_units()>164){
    digitalWrite (Gingerale, LOW);                                    //pump 2 on
  }
  digitalWrite (Gingerale, LOW);                                      //pump 2 off
      lcd.print("Drink Made");//Prints drink is ready
      delay(5000);
      lcd.clear();// resets LCD
      lcd.print("Drink 1");
      drink = d1; //returns to start
}


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
