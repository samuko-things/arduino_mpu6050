#include "mpu6050_imu.h"
#include <imu_madgwick_filter.h>

///////////////////////////////////////
float axOff = 0.877731;
float ayOff = -0.417400;
float azOff = 0.335485;

float gxOff = -0.046631;
float gyOff = 0.010792;
float gzOff = -0.003730;

float axCal = 0.00;
float ayCal = 0.00;
float azCal = 0.00;

float gxCal = 0.00;
float gyCal = 0.00;
float gzCal = 0.00;

float roll = 0.00;
float pitch = 0.00;
float yaw = 0.00;

float filterGain = 0.1;
////////////////////////////////////////

String msg;
MPU6050_IMU mpu6050_imu;
ImuMadgwickFilter madgwickFilter;

unsigned long serialCommTime, serialCommSampleTime = 10; // ms -> (1000/sampleTime) hz
unsigned long readImuTime, readImuSampleTime = 5;        // ms -> (1000/sampleTime) hz

void setup()
{
  /* Serial to display data */
  Serial.begin(115200);

  mpu6050_imu.init();

  madgwickFilter.setAlgorithmGain(filterGain);
  madgwickFilter.setDriftBiasGain(0.0);
  madgwickFilter.setWorldFrameId(0); // 0 - NWU, 1 - ENU, 2 - NED (I'm using NWU reference frame)

  delay(3000);

  readImuTime = millis();
}

void loop()
{
  if ((millis() - readImuTime) >= readImuSampleTime)
  {
    //------------READ ACC DATA (m/s^2) AND CALIBRATE---------------//
    float axRaw, ayRaw, azRaw;
    mpu6050_imu.get_acc_mps2(axRaw, ayRaw, azRaw);

    axCal = axRaw - axOff;
    ayCal = ayRaw - ayOff;
    azCal = azRaw - azOff;
    //------------------------------------------------------//

    //-----------READ GYRO DATA (rad/s) AND CALIBRATE---------------//
    float gxRaw, gyRaw, gzRaw;
    mpu6050_imu.get_gyro_radps(gxRaw, gyRaw, gzRaw);

    gxCal = gxRaw - gxOff;
    gyCal = gyRaw - gyOff;
    gzCal = gzRaw - gzOff;
    //-----------------------------------------------------//

    //-------- APPLY MADWICK FILTER IN NWU FRAME ----------//
    madgwickFilter.madgwickAHRSupdateIMU(gxCal, gyCal, gzCal, axCal, ayCal, azCal);

    //if you have a magnetometer use this:
    //madgwickFilter.madgwickAHRSupdate(gxCal, gyCal, gzCal, axCal, ayCal, azCal, mxCal, myCal, mzCal);

    madgwickFilter.getOrientationRPY(roll, pitch, yaw);
    // ----------------------------------------------------//

    msg = "RPY: [" + String(roll, 4) + "," + String(pitch, 4) + "," + String(yaw, 4) + "]";
    Serial.println(msg);
    Serial.println();

    // Serial.print(roll, 4);
    // Serial.print(", ");
    // Serial.print(pitch, 4);
    // Serial.print(", ");
    // Serial.println(yaw, 4);

    readImuTime = millis(); 
  }


  //------WRITE YOUR CODE HERE -------------//

  

  //----------------------------------------//
}