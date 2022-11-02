
#include <Controllino.h>
#include "define.h"
#include "ShuttersFunctions.h"

void pinSetupShutters()
{
    for (int i = 0; i < NUM_SHUTTERS * 2; i++)
    {
        pinMode(CONTROLLINO_D0 + i, OUTPUT);
        digitalWrite(CONTROLLINO_D0 + i, LOW);
    }
    PCICR |= B00000100;  // ENBALBE Pin change interrupt PORT K
    PCMSK2 |= B00111111; // Set PCINT16-23 (A8-A15) to trigger an interrupt on state change.
}

void timmershutterState(unsigned long &_timmershutters)
{
    if (millis() - _timmershutters >= shutters_delay)
    {
        for (int i = 0; i < NUM_SHUTTERS * 2; i++)
        {
            digitalWrite(CONTROLLINO_D0 + i, LOW);
        }
        _timmershutters = millis();
    }
}

void moveShutter(int shutter, enum shutter_directions _direction)
{
    digitalWrite(CONTROLLINO_D0 + shutter, LOW);
    digitalWrite(CONTROLLINO_D0 + shutter + 1, LOW);
    switch (_direction)
    {
    case BACKWARDS:
        Serial.println("Left");
        digitalWrite(CONTROLLINO_D0 + shutter, HIGH);
        break;
    case FORWARDS:
        Serial.println("Right");
        digitalWrite(CONTROLLINO_D0 + shutter + 1, HIGH);
        break;
    default:
        Serial.println("Default");
        digitalWrite(CONTROLLINO_D0 + shutter, LOW);
        digitalWrite(CONTROLLINO_D0 + shutter + 1, LOW);
        break;
    }
}