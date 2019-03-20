int lightPen1 = A0; //define a pin for Photo resistor of bottle 1
int lightPen2= A1 ; //define a pin for Photo resistor of bottle 2
int lightPen3= A2 ; //define a pin for Photo resistor of bottle 3
int full1=analogRead(lightPen1);//sets initial condition for bottle 1
int full2=analogRead(lightPen2);//sets initial condition for bottle 2
int full3=analogRead(lightPen3);//sets initial condition for bottle 3
  

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
analogReference(INTERNAL);
}

void loop()
{
  if (analogRead(lightPen1)<.8*full1){ //Tests to see if bottle 1 is empty
  Serial.println("Bottle 1 Empty");
  delay(10);
  }
  if (analogRead(lightPen2)<.8*full2){ // Test to see if bottle 2 is empty
  Serial.println("Bottle 2 Empty");
  delay(10);
  }
  if (analogRead(lightPen3)<.8*full3){ // Tests to see if bottle 3 is empty
  Serial.println("Bottle 3 Empty");
  delay(10);
  }

}
