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
const int i1;
const int i2;
const int i3;
bool make = false;
enum Drink {
  d1,
  d2,
  d3,
  strong,
  virgin,
  regular,
  sure
};

Drink drink = d1;

void setup() {
  // Debugging output
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode (i1, INPUT);
  pinMode(i2, INPUT);
  pinMode(i3, INPUT);
  lcd.print("Drink 1");
  
}

uint8_t i = 0;
void loop() {
  
  lcd.setCursor(0, 0);
  uint8_t buttons = lcd.readButtons();

  /*if (buttons) {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
      lcd.setBacklight(RED);
      }
      if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(YELLOW);
      }
    if (buttons & BUTTON_LEFT) {
      if (d == null) {
        lcd.print("LEFT ");
        lcd.setBacklight(GREEN);
      }
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      lcd.setBacklight(VIOLET);
    }*/
  if (make == false) {
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
          //digitalWrite(13,LOW);
          
        }
        break;

      case d2:

        if (buttons & BUTTON_RIGHT) {
          delay(500);
          lcd.print("Drink 3 ");
          drink = d3;
        }
        else if (buttons & BUTTON_LEFT) {
          //digitalWrite(9,HIGH);
          delay(500);
          //digitalWrite(9,LOW);
          lcd.print("Drink 1 ");
          drink = d1;
        }
        else if (buttons & BUTTON_SELECT) {
          lcd.setBacklight(GREEN);
          digitalWrite(7, HIGH);
          delay(500);
          //digitalWrite(7,LOW);
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
          //digitalWrite(5,LOW);
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

          strength = "regular";
          //call to drink function
          drink = sure;
        }
        else if (buttons & BUTTON_UP) {
          drink = d1;
          d = "";
          lcd.print("Drink 1 ");
          lcd.setBacklight(WHITE);
          digitalWrite(3,LOW);
          digitalWrite(5,LOW);
          digitalWrite(7,LOW);
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

          
          //call to drink function
          drink = sure;

          strength = "strong";
          //call to drink function
          
        }
        else if (buttons & BUTTON_UP) {
          drink = d1;
          d = "";
          lcd.print("Drink 1 ");
          lcd.setBacklight(WHITE);
          digitalWrite(3,LOW);
          digitalWrite(5,LOW);
          digitalWrite(7,LOW);
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

          
          //call to drink function
          drink = sure;
          strength = "virgin";
          //call to drink function
          
        }
        else if (buttons & BUTTON_UP) {
          drink = d1;
          d = "";
          lcd.print("Drink 1 ");
          lcd.setBacklight(WHITE);
          digitalWrite(3,LOW);
          digitalWrite(5,LOW);
          digitalWrite(7,LOW);
          delay(500);
        }
        break;

        case sure:
        if (buttons & BUTTON_SELECT) {
          delay(500);
          lcd.print("Making       ");
          
          //call to drink function
          Serial.println(strength);
          make = true;
        }
        else if (buttons & BUTTON_UP) {
          lcd.clear();
          drink = d1;
          d = "";
          strength = "";
          lcd.print("Drink 1 ");
          lcd.setBacklight(WHITE);
          digitalWrite(3,LOW);
          digitalWrite(5,LOW);
          digitalWrite(7,LOW);
          delay(500);
        }
        break;
    }
  }
//  else {
//    //check suppiles
//    int c [3];
//    c = check();
//    // make drink
//  }
}
