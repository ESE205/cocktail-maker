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
enum Drink {
  d1,
  d2,
  d3,
  strong,
  virgin,
  regular
};

Drink drink = d1;

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.print("Drink 1");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
}

uint8_t i = 0;
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
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
  if (strength == "") {
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
          lcd.print("Making ");

          strength = "regular";
          //call to drink function
          Serial.println(strength);
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
          lcd.print("Making ");

          strength = "strong";
          //call to drink function
          Serial.println(strength);
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
          lcd.print("Making ");
          strength = "virgin";
          //call to drink function
          Serial.println(strength);
        }
        break;
    }
  }
}