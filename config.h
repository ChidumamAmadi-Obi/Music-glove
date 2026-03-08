#pragma once

#include <stdint.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// pin numbers
#define BUTTON1 34
#define BUTTON2 35
#define BUTTON3 32
#define BUTTON4 33
#define LED1 25
#define LED2 26
#define LED3 27

// other macros
#define NUM_SONGS 5 // assume there are 5 songs in total
#define MAX_VOLUME 100
#define GYRO_THRESHOLD 75 // this controls the threshold at which a music parameter is changed eg if the gyro is greater than 75 degrees inthe x axis the volume will be changed

// structs will be used to pass sensor information easily and cleanly to the application
typedef struct{ // this struct holds sensor values detected by the MPU
  float gyroX; // rotation along x axis
  float gyroY; // rotation along y axis
  float gyroZ; // rotation along z axis

  float accX; // acceleration along x axis
  float accY; // acceleration along y axis
  float accZ; // acceleration along z axis

  float tempurature; // tempurature reccorded by MPU in degrees C
}MPUSensorValues;
typedef struct{
  bool one=0;
  bool two=0;
  bool three=0;
  bool four=0;
}Buttons;
typedef struct{
  uint8_t volume = 10; // volume can be 0-100
  uint8_t song = 0;
  uint8_t pitch = 0;
}MusicParameters;

// define structs
Adafruit_MPU6050 mpu; // makes an MPU object to be used durin initialization
MPUSensorValues mpuSensorValues;
Buttons button;
