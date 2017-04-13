#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include "Arduino.h"
#include <MySensors.h>

#define CHILD_ID_LIGHT 3

int lastLightLevel;
MyMessage ldrMsg(CHILD_ID_LIGHT, V_LIGHT_LEVEL);

class LDRSensor {
  private:
    uint8_t _pin;

  public:
    LDRSensor(uint8_t pin)
    {
      _pin = pin;
    }

    void begin()
    {
      Serial.println("Setting up LDR Sensor");
    }

    void sync()
    {
      int lightLevel = 100 - ((1023 - analogRead(_pin)) / 10.23);
      Serial.print("Light level: "); Serial.println(lightLevel);
      if (lightLevel != lastLightLevel) {
          send(ldrMsg.set(lightLevel));
          lastLightLevel = lightLevel;
      }
    }

     void present(uint8_t child = CHILD_ID_LIGHT)
     {
        // Register all sensors to gw (they will be created as child devices)
        ::present(child, S_LIGHT_LEVEL);
     }
};

#endif
