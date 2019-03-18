 /*
This is code to control 4 to 16 channel 5V Relay module using Arduino
 * watch the video on how to use 4 to unlimited Relay channels  https://youtu.be/Wbm3MCMgM_s
 
 */
/*
 *  This code is written by Ahmad Shamshiri for Robojax.com
// Written Mar 26, 2018 at 12:14 in Ajax, Ontario, Canada

 *  
 */

int ch = 3;// number of relays you got
int relay[]={3,4,5}; // Arduino pin numbers. the same number of relay should be defined here as input pins


int wait = 2000;// delay time
int i=0;

void setup() {
    Serial.begin(9600);// prepare Serial monitor
    // set  pins as output

 
    pinMode(relay[0], OUTPUT);// connected to relay1
    digitalWrite(relay[0], HIGH); // Turn the relay OFF  

    pinMode(relay[1], OUTPUT);// connected to relay2
    digitalWrite(relay[1], HIGH); // Turn the relay OFF  

    pinMode(relay[2], OUTPUT);// connected to relay3
    digitalWrite(relay[2], HIGH); // Turn the relay OFF  
               
    Serial.println("4 Relay Test");
}

void loop() {
    
     
 for(int i=0; i < ch; i++)
 {
      Serial.print("Relay "); Serial.print(i+1);Serial.println(" ON");
      digitalWrite(relay[i], LOW); // Turn the relay ON    
      delay(wait); 
      Serial.print("Relay "); Serial.print(i+1);Serial.println(" OFF");
      digitalWrite(relay[i], HIGH); // Turn the relay OFF    
      delay(wait); 
 }// for loop


    Serial.println("====== loop done ==");

}// loop
