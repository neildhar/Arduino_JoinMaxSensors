/*
  JoinMaxSensors.cpp - Library for using JoinMax Sensors with Arduino
  Created by Senor Neil Dhar, October 23, 2013.
*/
#include <Arduino.h>
#include <Wire.h>
#include "JoinMaxSensors.h";

using namespace JM;

ultrasonicSensor::ultrasonicSensor(TwoWire * _bus, int _epin) : i2cBus(_bus), enablePin(_epin) {
	if(enablePin!=-1) pinMode(enablePin, OUTPUT);
}
ultrasonicSensor::ultrasonicSensor(TwoWire * _bus): i2cBus(_bus), enablePin(-1) {}
int ultrasonicSensor::read(){
  if(enablePin!=-1) digitalWrite(enablePin, HIGH);
  i2cBus->requestFrom(I2C_Address,2);
  while(!i2cBus->available()){delayMicroseconds(1);}
  char high = i2cBus->read();
  unsigned char low = i2cBus->read();
  if(enablePin!=-1) digitalWrite(enablePin, LOW);
  return (int)(high*256+low);
}



compassSensor::compassSensor(TwoWire * _bus) : i2cBus(_bus){}
int compassSensor::read(){
  i2cBus->requestFrom(I2C_Address,2);
  while(!i2cBus->available()){}
  char high = i2cBus->read();
  unsigned char low = i2cBus->read();
  int result = (int)(high*256+low);
  return result<181?result:result-360;
}



compoundEye::compoundEye(TwoWire * _bus) : i2cBus(_bus) {}
void compoundEye::initialize(){
  i2cBus->beginTransmission(I2C_Address);
  i2cBus->write(14);
  i2cBus->endTransmission();
  i2cBus->requestFrom(I2C_Address,1);
  while(i2cBus->available()) i2cBus->read();
}
int compoundEye::highestValue(){
  this->initialize();
  i2cBus->beginTransmission(I2C_Address);
  i2cBus->write(9);
  i2cBus->endTransmission();
  i2cBus->requestFrom(I2C_Address,1);
  while(!i2cBus->available()){}
  return (int) i2cBus->read();
}
int compoundEye::highestBulb(){
  this->initialize();
  i2cBus->beginTransmission(I2C_Address);
  i2cBus->write(8);
  i2cBus->endTransmission();
  i2cBus->requestFrom(I2C_Address,1);
  while(!i2cBus->available()){}
  return 8-((int)i2cBus->read());
}
int compoundEye::readBulb(int bulb){
  int command = bulb<=4?5-bulb:12-bulb; 
  this->initialize();
  i2cBus->beginTransmission(I2C_Address);
  i2cBus->write(command);
  i2cBus->endTransmission();
  i2cBus->requestFrom(I2C_Address,1);
  while(!i2cBus->available()){}
  return (int)i2cBus->read();
}
