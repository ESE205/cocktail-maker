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
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

String strength;//Strength of Drink (strong,regular,virgin)
String d;       // Which Drink you are selecting(1,2,3)
String pDrink; //What is this????????????????????????????????????????????????????????????????????????????????????

float w1 = 2;//The predetermind weights of what?????????????????????????????????????????????????????????
float w2 = 3;// what are these???????????????????????????????????????????????????????????
float w3 = 5;//what are these???????????????????????????????????????????????????????????????????

bool b1 = false;// check checking what?????????????????????????????????????????????????????????
bool b2 = false;// what do these mean??????????????????????????????????????????????????
bool b3 = false;
String b = "check b: ";

int lightPen1 = A0; //define a pin for Photo resistor of bottle 1
int lightPen2 = A1 ; //define a pin for Photo resistor of bottle 2
int lightPen3 = A2 ; //define a pin for Photo resistor of bottle 3
int full1 = analogRead(lightPen1); //sets initial condition for bottle 1
int full2 = analogRead(lightPen2); //sets initial condition for bottle 2
int full3 = analogRead(lightPen3); //sets initial condition for bottle 3


enum Drink { // state machine for???????????????????????????????????????????????
  d1,
  d2,
  d3,
  setI1,
  setI2,
  setI3,
  strong,
  virgin,
  regular,
  sure,
  check,
  m1,
  m2,
  m3
};

Drink drink = d1; // state machine what is this for???????????????????????????????????????????

void setup() {
  // Debugging output
  Serial.begin(9600);
  
  scale.begin(DOUT, CLK);// scale
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  analogReference(INTERNAL);
  
  lcd.begin(16, 2); //LCD 
  lcd.print("Drink 1");

}

uint8_t i = 0;
void loop() {
//EXPLAIN THESE STEPS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  lcd.setCursor(0, 0);//LCD
  uint8_t buttons = lcd.readButtons();//LCD
  //weight(5);

  switch (drink) {//State Machine WHAT DO EACH OF THE STATES MEAN????
    case d1:
      if (buttons & BUTTON_RIGHT) {//swtiches state FROM WHAT TO WHAT?????????????????????????????????????????????????
        delay(500);
        lcd.print("Drink 2 ");
        drink = d2;
      }
      else if (buttons & BUTTON_LEFT) {//swtiches state
        delay(500);
        lcd.print("Drink 3 ");
        drink = d3;
      }
      else if (buttons & BUTTON_SELECT) {//swtiches state
        digitalWrite(3, HIGH);
        lcd.setBacklight(RED);
        delay(500);
        lcd.print("Regular ");
        drink = setI1;
        d = "d1";
        Serial.println(d);


      }
      break;

    case d2:

      if (buttons & BUTTON_RIGHT) {//swtiches state
        delay(500);
        lcd.print("Drink 3 ");
        drink = d3;
      }
      else if (buttons & BUTTON_LEFT) {//swtiches state

        delay(500);

        lcd.print("Drink 1 ");
        drink = d1;
      }
      else if (buttons & BUTTON_SELECT) {//swtiches state
        lcd.setBacklight(GREEN);
        digitalWrite(7, HIGH);
        delay(500);

        lcd.print("Regular ");
        drink = setI1;
        d = "d2";
        Serial.println(d);
      }
      break;

    case d3:
      if (buttons & BUTTON_RIGHT) {//Change ingredents
        delay(500);
        lcd.print("Drink 1 ");
        drink = d1;
      }
      else if (buttons & BUTTON_LEFT) {//Change ingredents
        delay(500);
        lcd.print("Drink 2 ");
        drink = d2;
      }
      else if (buttons & BUTTON_SELECT) {//Change ingredents
        digitalWrite(5, HIGH);
        lcd.setBacklight(YELLOW);
        delay(500);

        lcd.print("Regular ");
        drink = setI1;
        d = "d3";
        Serial.println(d);

      }
      break;

      //What is this telling us to do???????
   case setI1:
      if (d == pDrink) {// Drinks are the same as the previous therefore what happens????????????????????????????????????????????
        d = regular;
        lcd.print("Regular     ");
        break;
      }
      else if (d == "d1") {// Drinks differ and.....??????????????????????????????????????????????????????????????????????
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;
          break;
        }
      }
      else if (d == "d2") { // what is this?????????????????????????????????????????????????
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;
          break;
        }
      }
      else if (d == "d3") {
        lcd.print("i1 to bottle1");
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i2 to bottle2");
          drink = setI2;
          break;
        }
      }

    case setI2:
      if (d == "d1") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;
          break;
        }
      }
      else if (d == "d2") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;
          break;
        }
      }
      else if (d == "d3") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("i3 to bottle3");
          drink = setI3;
          break;
        }
      }

 
case setI3: //After this state, the drinks switch 
      if (d == "d1") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("Regular    ");
          drink = regular;
          break;
        }
      }
      else if (d == "d2") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("Regular     ");
          drink = regular;
          break;
        }
      }
      else if (d == "d3") {
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("Regular       ");
          drink = regular;
          break;
        }
      }
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
      else if (buttons & BUTTON_SELECT) {//Strength seleceted
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
      else if (buttons & BUTTON_SELECT) {//Strength seleceted
        delay(500);
        lcd.print("Are you sure: ");
        drink = sure;

        strength = "strong";
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
      else if (buttons & BUTTON_SELECT) {//Strength selected
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
      if (buttons & BUTTON_SELECT) { //Checks
        delay(500);
        lcd.print("Making      ");
        pDrink = d;
        Serial.print(d);
        Serial.print(" ");
        Serial.print(strength);
        drink = check;
      }
      else if (buttons & BUTTON_UP) {//return to start
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
      lcd.print("making");
      //      bool glass = weight(w1);
      //      if (glass) {// checks weight
      drink = m2; // switches motors
      //        break;
      //      }
      break;
    case m2:

      //      bool glass = weight(w2);
      //      if (glass) {// checks weight
      drink = m3;// switches motors
      //        break;
      //      }
      break;
    case m3:
      //
      //      bool glass = weight(w3);
      //      if (glass) {// checks weight
      lcd.print("Drink Made");
      delay(5000);
      lcd.clear();
      lcd.print("Drink 1");
      drink = d1; //returns to start
      //        break;
      //      }
      break;
  }

}


// helper methods

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

bool weight(float w) { //what is this???????????????????????????????????????????????????????????????????????????
  Serial.print("Reading: ");
  float r = scale.get_units(); //scale.get_units() returns a float
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  if (w >= r) {
    return true;
  }
  return false;

}
