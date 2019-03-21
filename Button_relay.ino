 /*
This is code to control 4 to 16 channel 5V Relay module using Arduino
 * watch the video on how to use 4 to unlimited Relay channels  https://youtu.be/Wbm3MCMgM_s
 
 */
/*
 *  This code is written by Ahmad Shamshiri for Robojax.com
// Written Mar 26, 2018 at 12:14 in Ajax, Ontario, Canada

 *  
 */

#include "HX711.h"

int ch = 3;// number of relays you got
int relay[]={2,3,4}; // Arduino pin numbers. the same number of relay should be defined here as input pins


int wait = 2000;// delay time


void setup() {
    Serial.begin(9600);// prepare Serial monitor
    // set  pins as output

    pinMode(relay[0], OUTPUT);// connected to relay1
    digitalWrite(relay[0], HIGH); // Turn the relay OFF  

    pinMode(relay[1], OUTPUT);// connected to relay2
    digitalWrite(relay[1], HIGH); // Turn the relay OFF  

    pinMode(relay[2], OUTPUT);// connected to relay3
    digitalWrite(relay[2], HIGH); // Turn the relay OFF  
               
    Serial.println("3 Relay Test");
}

void loop() {
    
if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '1') {
      Serial.print("Relay 1 ON");
      digitalWrite(relay[0], LOW); // Turn the relay ON
      delay(100); 
      digitalWrite(relay[1], HIGH); // Turn the relay OFF
      delay(100);
      digitalWrite(relay[2], HIGH); // Turn the relay OFF
      delay(100);
    }
    else if(temp == '2') {
      
      Serial.print("Relay 2 ON");
      digitalWrite(relay[1], LOW); // Turn the relay ON 
      delay(100);
      digitalWrite(relay[0], HIGH); // Turn the relay OFF
      delay(100);
      digitalWrite(relay[2], HIGH); // Turn the relay OFF
      delay(100);
    } 
    
    else if(temp == '3') {
      Serial.print("Relay 3 ON");
      digitalWrite(relay[2], LOW); // Turn the relay ON 
      delay(100);
      digitalWrite(relay[1], HIGH); // Turn the relay OFF
      delay(100);
      digitalWrite(relay[0], HIGH); // Turn the relay OFF
      delay(100);
    }
        else if(temp == '0') {
      Serial.print("Relay 3 ON");
      digitalWrite(relay[2], HIGH); // Turn the relay ON 
      delay(100);
      digitalWrite(relay[1], HIGH); // Turn the relay OFF
      delay(100);
      digitalWrite(relay[0], HIGH); // Turn the relay OFF
      delay(100);
    }

    
 }// for loop


    Serial.println("====== loop done ==");

}// loop
