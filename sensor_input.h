#pragma once

#include "config.h"
#include "leds.h"

// reference for MPU code https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

void initMPU() { // this is needed to set up the MPU and make sure its working
  if (!mpu.begin()) { // attempt to initialize!
    Serial.println("Failed to find MPU6050 chip");
    while (1) { // loop forever if MPU failed to initialize
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G"); break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G"); break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G"); break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G"); break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s"); break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s"); break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s"); break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s"); break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz"); break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz"); break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz"); break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz"); break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz"); break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz"); break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz"); break;
  }
  mpu.enableSleep(false);  // Make sure sensor is awake
}
MPUSensorValues scanMPU(){ // get x y z information from MPU and store in variable
  sensors_event_t a, g, temp; // stores acceleration information (a) gyroscope information (b) and tempurature information (temp)
  static MPUSensorValues mpuSensorValues; // create struct to hold the recorded information from the MPU

  mpu.getEvent(&a, &g, &temp); // get the informatin from the mpu

  // store the information into the struct
  mpuSensorValues.gyroX = g.gyro.x;
  mpuSensorValues.gyroY = g.gyro.y;
  mpuSensorValues.gyroZ = g.gyro.z;

  mpuSensorValues.accX = a.acceleration.x;
  mpuSensorValues.accY = a.acceleration.y;
  mpuSensorValues.accZ = a.acceleration.z;

  mpuSensorValues.tempurature = temp.temperature;

  //Serial.print("gyro x: "); Serial.println(g.gyro.x,6);
  //Serial.print("gyro y: "); Serial.println(g.gyro.y,6);
  //Serial.print("gyro z: "); Serial.println(g.gyro.z,6);

  //Serial.print("acceleration x: "); Serial.println(a.acceleration.x);
  //Serial.print("acceleration y: "); Serial.println(a.acceleration.y);
  //Serial.print("acceleration z: "); Serial.println(a.acceleration.z);  

  //Serial.print("tempurature: "); Serial.println(mpuSensorValues.tempurature);  

  return mpuSensorValues; // return the information
}
//*** unfinished do not use
void musicControl(MPUSensorValues mpuSensorValues, MusicParameters*musicParameters){
  // only change parameter after a delay as to not rapidly increase/decrease a parameter

// CONTROL SONG
  if (mpuSensorValues.gyroX > 0 && mpuSensorValues.gyroX <= GYRO_THRESHOLD) { // if hand right change song
    if (musicParameters->song == NUM_SONGS) musicParameters->song=0; // if the last song is reached, switch to the first song
    else musicParameters->song++; // change song
  }

// CONTROL VOLUME
  if (mpuSensorValues.gyroZ > 0 && mpuSensorValues.gyroZ <= GYRO_THRESHOLD){ // if hand up increase volume
    if (musicParameters->volume >= MAX_VOLUME) musicParameters->volume=MAX_VOLUME; // if the volume is at its max, dont increase the volume
    else musicParameters->volume++; // increase volume by 1
  } else if (mpuSensorValues.gyroZ < 0 && mpuSensorValues.gyroZ >= -GYRO_THRESHOLD){ // if hand down decrease volume
    if (musicParameters->volume == 0) musicParameters->volume=0; // if the volume is already 0, dont decrease the volume
    else musicParameters->volume--; // decrease volume by 1
  }
}
//***



void controlTouchSensors(){ // keep track of button states to send to app via bluetooth
  if (digitalRead(BUTTON1)) {
    button.one=true;
  } else {
    button.one=false;
  }

  if (digitalRead(BUTTON2)) {
    button.two=true;
  } else {
    button.two=false;
  }

  if (digitalRead(BUTTON3)) {
    button.three=true;
  } else {
    button.three=false;
  }

  if (digitalRead(BUTTON4)) {
    button.four=true;
  } else {
    button.four=false;
  }

  toggleLEDs(button); // handle led flashing 
}

