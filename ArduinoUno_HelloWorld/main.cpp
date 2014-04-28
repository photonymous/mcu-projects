#include "main.h"


void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() 
{
  for(int ii = 1; ii < 201; ii++)
  {
  	digitalWrite(13, HIGH);
  	delay(ii);
  	digitalWrite(13, LOW);
  	delay(ii);
  }
/*
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
*/
}

MAIN
