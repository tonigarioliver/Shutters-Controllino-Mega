#include <Controllino.h>
#include "define.h"
#include "ShuttersFunctions.h"

volatile bool AnalogState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};
volatile bool AnalogOldState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};

int dir = 0;
unsigned long timmer = 0;
unsigned long timmershutters = 0;
enum shutter_directions
{
  BACKWARDS,
  FORWARDS
};

ISR(PCINT2_vect)
{
  for (int i = 0; i < NUM_SHUTTERS; i++)
  {
    if (digitalRead(CONTROLLINO_A8 + i) != AnalogSTATE[i])
    {
      // Pin D2 triggered the ISR on a Falling pulse
      AnalogSTATE[i] != AnalogSTATE[i];
    }
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  pinSetupShutters();
}

void loop()
{
  // put your main code here, to run repeatedly:
  timmershutterState(timmershutters);
  checkShuttersState(AnalogState, AnalogOldState);
  if (millis() - timmer >= timmerdelay)
  {
    timmer = millis();
    // move motor
    if (dir == 0)
    {
      dir = 1;
      moveShutter(0, FORWARDS);
    }
    else
    {
      dir = 0;
      moveShutter(0, BACKWARDS);
    }
  }
}