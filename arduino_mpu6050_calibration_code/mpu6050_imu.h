#ifndef MPU6050_IMU_H
#define MPU6050_IMU_H

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <math.h>
#include <Wire.h>


class MPU6050_IMU
{
public:
  void init()
  {
    Wire.begin(); // Initialize comunication

    Wire.beginTransmission(MPU6050_ADDRESS); // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                        // Talk to the register 6B
    Wire.write(0x00);                        // Make reset - place a 0 into the 6B register
    Wire.endTransmission();                  // end the transmission
  }

  void init(int mpu6050_address)
  {
    MPU6050_ADDRESS = mpu6050_address;

    Wire.begin(); // Initialize comunication

    Wire.beginTransmission(MPU6050_ADDRESS); // Start communication with MPU6050 // MPU=0x68
    Wire.write(0x6B);                        // Talk to the register 6B
    Wire.write(0x00);                        // Make reset - place a 0 into the 6B register
    Wire.endTransmission();                  // end the transmission
  }

  void get_acc_mps2(float &ax, float &ay, float &az)
  {
    // === Read acceleromter data === //
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x3B); // Start with register 0x3B (accEL_XOUT_H)
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDRESS, 6); // Read 6 registers total, each axis value is stored in 2 registers

    // get raw accelerometer data
    accX = Wire.read() << 8 | Wire.read(); 
    accY = Wire.read() << 8 | Wire.read();
    accZ = Wire.read() << 8 | Wire.read(); 

    // For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
    float accX_g = (float)accX / 16384.00;
    float accY_g = (float)accY / 16384.00;
    float accZ_g = (float)accZ / 16384.00;

    // convert to m/s2
    ax = accX_g * 9.8;
    ay = accY_g * 9.8;
    az = accZ_g * 9.8;
  }

  void get_gyro_degps(float &gx, float &gy, float &gz)
  {
    // === Read gyroscope data === //
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x43); // gyro data first register address 0x43
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDRESS, 6); // Read 4 registers total, each axis value is stored in 2 registers

    // get raw gyro data
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();

    // convert raw gyro to rad/sec
    // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    gx = (float)gyroX / 131.0;
    gy = (float)gyroY / 131.0;
    gz = (float)gyroZ / 131.0;
  }

  void get_gyro_radps(float &gx, float &gy, float &gz)
  {
    // === Read gyroscope data === //
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(0x43); // gyro data first register address 0x43
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDRESS, 6); // Read 4 registers total, each axis value is stored in 2 registers

    // get raw gyro data
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();

    // convert raw gyro to rad/sec
    // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    // then multiply by PI/180 (i.e 0.017453293)
    gx = ((float)gyroX / 131.0) * 0.017453293;
    gy = ((float)gyroY / 131.0) * 0.017453293;
    gz = ((float)gyroZ / 131.0) * 0.017453293;
  }

private:
  int MPU6050_ADDRESS = 0x68; // MPU6050 I2C address
  int accX, accY, accZ;
  int gyroX, gyroY, gyroZ;

};

#endif // MPU6050_IMU_H
