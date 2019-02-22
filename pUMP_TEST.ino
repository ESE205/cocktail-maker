
const int motorA=5;
const int motorArev=6;
 
   void setup() {
  // put your setup code here, to run once:
   //Sets up motor inputs
    Serial.begin(9600);
    pinMode(5,OUTPUT );
    pinMode(6,OUTPUT);
  
}

void loop() {
//Turn motor clockwise for 2 seconds
digitalWrite(motorA,HIGH);
digitalWrite(motorArev,LOW);
delay(5000);
//Turn motor counter-clockwise for 2 seconds
digitalWrite(motorA,LOW);
digitalWrite(motorArev,HIGH);
delay(5000);
  }

