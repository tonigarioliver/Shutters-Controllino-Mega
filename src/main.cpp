#include <Controllino.h>
#include "define.h"
#include "ShuttersFunctions.h"

volatile bool AnalogState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};
volatile bool AnalogOldState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};
bool newstates[NUM_SHUTTERS] = {false,false,false,false,false};

int dir = 0;
unsigned long timmer = 0;
unsigned long timmershutters = 0;
int test = LOW;

ISR(PCINT2_vect)
{
  for (int i = 0; i < NUM_SHUTTERS; i++)
  {
    if (digitalRead(CONTROLLINO_A8 + i) != AnalogState[i])
    {
      // Pin D2 triggered the ISR on a Falling pulse
      AnalogState[i] =! AnalogState[i];
    }
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println("Serial Ready");
  pinSetupShutters();

  pinMode(CONTROLLINO_D13, OUTPUT);
  digitalWrite(CONTROLLINO_D13, HIGH);
}

void loop()
{
  // put your main code here, to run repeatedly:
  timmershutterState(timmershutters);                                      // to check high output state
  bool newupdateShutter = checkShuttersState(AnalogState, AnalogOldState,newstates); // new updates
  if (newupdateShutter)
  {
    Serial.println("New updates");
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
      if (newstates[i] == true)
      {
        newstates[i] = false;
        if(AnalogOldState[i] == HIGH)
        {
          moveShutter(i, FORWARDS);
        }
        else
        {
          moveShutter(i, BACKWARDS);
        }
        Serial.print("Value shutter first"+ String(i)+":" +String(digitalRead(CONTROLLINO_D0 + i)));
        Serial.println("Value shutter second"+ String(i)+":" +String(digitalRead(CONTROLLINO_D0 + i+1)));
      }
    }
  }
  if(test != digitalRead(CONTROLLINO_A9)){
    test =! test;
  };
  if (millis() - timmer >= 5000){
    digitalWrite(CONTROLLINO_D13,!test);
    timmer = millis();
  }
}