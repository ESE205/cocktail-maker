/*This program is DrinkRobotMaiTie and makes the spectacular

* drink Margot's Mai Tai

* and was written by

*Ted Kinsman Rochester Institute of Technology

*March 2017 emkpph@rit.edu

*12 v DC motors pump 1 oz of liquor in 32 sec.

*/

#define Vodka 1 // (pump1)12VDC motor to pump vodka on pin 1

#define Gingerale 2 // (pump2) Gingerale connected to pin 2

#define CranMango 3 // (pump3) CranMango on pin 3

//int sensorPin = A0; // analog read : used to tell if doorbell switch is pushed

//int sensorValue = 0;  //value written to when analog value is read from doorbell


void setup()

{

pinMode(Vodka, OUTPUT);

pinMode(Gingerale, OUTPUT);

pinMode(CranMango, OUTPUT);

digitalWrite (Vodka, HIGH); //pump 1 off

digitalWrite (Gingerale, HIGH); //pump 2 off

digitalWrite (CranMango, HIGH); //pump 3 off

delay(1000); // let relays settle down before running the first time.

}

void loop()

//WILL NEED TO EDIT FOR CORRECT SERIAL READ
if (serial.read==Drink one Strong){
  while (get.units()<103){
    digitalWrite (Vodka, LOW); //pump 1 on
  }
  digitalWrite (Vodka, HIGH);// Turns pump 1 off
  while(get.units()<330 && get.units()>=103){
  digitalWrite (Gingerale, LOW); //pump 2 on
  }
  digitalWrite(Gingerale, HIGH); // Pump 2 off
}

//////////////////////////////////////////////////////////////////

if (serial.read==Drink one Regular){
  while (get.units()<55){
    digitalWrite (Vodka, LOW); //pump 1 on
  }
  digitalWrite (Vodka, HIGH);// Turns pump 1 off
  while(get.units()<330 && get.units()>=55){
  digitalWrite (Gingerale, LOW); //pump 2 on
  }
  digitalWrite(Gingerale, HIGH); // Pump 2 off
}  

///////////////////////////////////////////////////////////////////

if (Serial.read== Drink one virgin){
  while(get.units()<330){
  digitalWrite (Gingerale, LOW); //pump 2 on
  }
  digitalWrite(Gingerale, HIGH); // Pump 2 off
}

/////////////////////////////////////////////////////////////////////

if (Serial.read== Drink 2 Strong){
  while (get.units()<103){
    digitalWrite (Vodka, LOW); //pump 1 on
  }
  digitalWrite (Vodka, HIGH);// Turns pump 1 off
  while(get.units()<330 && get.units()>=103){
  digitalWrite (CranMango, LOW); //pump 3 on
  }
  digitalWrite(CranMango, HIGH); // Pump 3 off
}

///////////////////////////////////////////////////////////////////////

if (Serial.read== Drink 2 Regular){
  while (get.units()<55){
    digitalWrite (Vodka, LOW); //pump 1 on
  }
  digitalWrite (Vodka, HIGH);// Turns pump 1 off
  while(get.units()<330 && get.units()>=55){
  digitalWrite (CranMango, LOW); //pump 3 on
  }
  digitalWrite(CranMango, HIGH); // Pump 3 off
}

/////////////////////////////////////////////////////////////////////

if (Serial.read== Drink 2 Virgin){
    while(get.units()<330){
  digitalWrite (CranMango, LOW); //pump 3 on
  }
  digitalWrite(CranMango, HIGH); // Pump 3 off
}

////////////////////////////////////////////////////////////////

if (serial.read == Drink 3 Strong){
    while (get.units()<104){
    digitalWrite (Vodka, LOW);// pump 1 on
  }
  digitalWrite(Vodka, HIGH); //pump 1 off
    while (get.units()<217 && get.units()>103){
    digitalWrite (CranMango, LOW); //pump 3 on
  }
  digitalWrite (CranMango, LOW); //pump 3 off
    while (get.units()<331 && get.units()>216){
      digitalWrite (Vodka, LOW); //turns pump 2 on
  }
  digitalWrite(Vodka, HIGH); //turns pump 2 off

/////////////////////////////////////////////////////////////////////////
  
if (serial.read == Drink 3 Regular){
    while (get.units()<56){
    digitalWrite (Vodka, LOW);// pump 1 on
  }
  digitalWrite(Vodka, HIGH); //pump 1 off
    while (get.units()<192.5 && get.units()>55){
    digitalWrite (CranMango, LOW); //pump 3 on
  }
  digitalWrite (CranMango, LOW); //pump 3 off
    while (get.units()<331 && get.units()>218){
      digitalWrite (Gingerale, LOW); //turns pump 2 on
  }
  digitalWrite(Gingerale, HIGH); //turns pump 2 off

///////////////////////////////////////////////////////////////////////

if (serial.read == Drink 3 Virgin){
      while (get.units()<166){
    digitalWrite (CranMango, LOW);// pump 3 on
  }
  digitalWrite(CranMango, HIGH); //pump 3 off
    while (get.units()<331 && get.units()>164){
    digitalWrite (Gingerale, LOW); //pump 2 on
  }
  digitalWrite (Gingerale, LOW); //pump 2 off
    while (get.units()<331 && get.units()>218){
      digitalWrite (Gingerale, LOW); //turns pump 2 on
  }
  digitalWrite(Gingerale, HIGH); //turns pump 2 off
  
 
digitalWrite (PineLime, LOW); //low turns on relays to turn on pump


}

}
