/*This program is DrinkRobotMaiTie 

* and was written by

*Ted Kinsman Rochester Institute of Technology

*March 2017 emkpph@rit.edu

*12 v DC motors pump 1 oz of liquor in 32 sec.

*/

//Modifications by Cj Wilson this code will make 3 different drink combinations at 3 different strengths
// Each drink will be 330g. Strong=75g regular=40g

#define Vodka 3                                                       // (pump1)12VDC motor to pump vodka on pin 3

#define Gingerale 4                                                   // (pump2) Gingerale connected to pin 4

#define CranMango 5                                                   // (pump3) CranMango on pin 5

//int sensorPin = A0;                                                 // analog read : used to tell if doorbell switch is pushed

//int sensorValue = 0;                                                //value written to when analog value is read from doorbell


void setup()

{

pinMode(Vodka, OUTPUT);

pinMode(Gingerale, OUTPUT);

pinMode(CranMango, OUTPUT);

digitalWrite (Vodka, HIGH);                                           //pump 1 off

digitalWrite (Gingerale, HIGH);                                       //pump 2 off

digitalWrite (CranMango, HIGH);                                       //pump 3 off

delay(1000);                                                          // let relays settle down before running the first time.

}

void loop()

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

///////////////////////////////////////////////////////////////////
                                                                      //Vodka Gingerale virgin
if (d=="d1" && strength=="virgin"){
  while(scale.get_units()<331){
  digitalWrite (Gingerale, LOW);                                      //pump 2 on
  }
  digitalWrite(Gingerale, HIGH);                                      // Pump 2 off
}

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

/////////////////////////////////////////////////////////////////////
                                                                      //Vodka CranMango Virgin
if (d=="d2" && strength=="virgin"){
    while(scale.get_units()<331){
  digitalWrite (CranMango, LOW);                                      //pump 3 on
  }
  digitalWrite(CranMango, HIGH);                                      // Pump 3 off
}

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

}

}
