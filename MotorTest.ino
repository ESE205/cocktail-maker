void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(3,OUTPUT );
}

void loop() {
  // put your main code here, to run repeatedly:
    runMotor()
}

void runMotor(){
  if (millis() > 1 && < 2){
    digitalWrite(3,HIGH);
    delay(3000);
    digitalWrite3,LOW);
  }
}
