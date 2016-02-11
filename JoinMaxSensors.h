/*
  JoinMaxSensors.h - Library for using JoinMax Sensors with Arduino
  Created by Senor Neil Dhar, October 23, 2013.
*/

#ifndef JoinMaxSensors_h
#define JoinMaxSensors_h

#include <Arduino.h>

namespace JM{
  class ultrasonicSensor{
    private: 
      TwoWire * i2cBus;
      int enablePin;
      static const int I2C_Address = 0x04;
    public:
      ultrasonicSensor(TwoWire*);
      ultrasonicSensor(TwoWire*, int);
      int read();
  };
  
  class compassSensor{
    private: 
      TwoWire * i2cBus;
      static const int I2C_Address = 0x3B;
    public:
      compassSensor(TwoWire*);
      int read();
  };
  
  class compoundEye{
    private: 
      TwoWire * i2cBus;
      static const int I2C_Address = 0x01;
    public:
      compoundEye(TwoWire*);
      void initialize();
      int highestValue();
      int highestBulb();
      int readBulb(int);
  };
}
#endif
