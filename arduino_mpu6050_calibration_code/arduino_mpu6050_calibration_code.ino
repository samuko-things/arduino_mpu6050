#include "mpu6050_imu.h"

///////////////////////////////////////
const int DATA_LENGTH = 1000;

float axOff = 0.877731;
float ayOff = -0.417400;
float azOff = 0.335485;

float gxOff = -0.046631;
float gyOff = 0.010792;
float gzOff = -0.003730;
////////////////////////////////////////

MPU6050_IMU mpu6050_imu;

unsigned long readImuTime, readImuSampleTime = 100; // ms -> (1000/sampleTime) hz

void readCalAccGyr()
{
  String msg;

  if ((millis() - readImuTime) >= readImuSampleTime)
  {
    //------------ READ RAW ACC DATA (m/s^2) IN NWU FRAME ---------------//
    float axRaw, ayRaw, azRaw;
    mpu6050_imu.get_acc_mps2(axRaw, ayRaw, azRaw);

    //------------ APPLY OFFSET TO ACC DATA IN NWU FRAME ---------------//
    float ax = axRaw - axOff;
    float ay = ayRaw - ayOff;
    float az = azRaw - azOff;

    msg = "ACC Readings: [" + String(ax, 4) + "," + String(ay, 4) + "," + String(az, 4) + "]";
    Serial.println(msg);

    // Serial.print(ax, 4);
    // Serial.print(", ");
    // Serial.print(ay, 4);
    // Serial.print(", ");
    // Serial.println(az, 4);

    //----------- READ RAW GYRO DATA (rad/s) IN NWU FRAME ---------------//
    float gxRaw, gyRaw, gzRaw;
    mpu6050_imu.get_gyro_radps(gxRaw, gyRaw, gzRaw);

    //------------ APPLY OFFSET TO ACC DATA IN NWU FRAME ---------------//
    float gx = gxRaw - gxOff;
    float gy = gyRaw - gyOff;
    float gz = gzRaw - gzOff;

    msg = "GYR Readings: [" + String(gx, 4) + "," + String(gy, 4) + "," + String(gz, 4) + "]";
    Serial.println(msg);
    Serial.println();

    // Serial.print(gx, 4);
    // Serial.print(", ");
    // Serial.print(gy, 4);
    // Serial.print(", ");
    // Serial.println(gz, 4);

    readImuTime = millis();
  }
}

void calibrateAccGyr()
{
  axOff = 0.00;
  ayOff = 0.00;
  azOff = 0.00;

  gxOff = 0.00;
  gyOff = 0.00;
  gzOff = 0.00;

  String msg;
  int count;

  //------------------- COMPUTE ACC OFFSET ------------------------------//
  count = 0;

  msg = "Computing ACC Offset ...";
  Serial.println();
  Serial.println(msg);

  while (count < DATA_LENGTH)
  {
    float axRaw, ayRaw, azRaw;
    mpu6050_imu.get_acc_mps2(axRaw, ayRaw, azRaw);
    axOff += axRaw;
    ayOff += ayRaw;
    azOff += azRaw;

    // Serial.print(count);
    count += 1;

    delay(10);
  }

  axOff = axOff / (float)DATA_LENGTH;
  ayOff = ayOff / (float)DATA_LENGTH;
  azOff = (azOff / (float)DATA_LENGTH) - 9.8;

  msg = "ACC Offset: [" + String(axOff, 6) + "," + String(ayOff, 6) + "," + String(azOff, 6) + "]";
  Serial.println(msg);

  //---------------------------------------------------------------------------------//

  //----------------------- COMPUTE GYRO OFFSET -------------------------------------//
  float min_x = 0.00, max_x = 0.00;
  float min_y = 0.00, max_y = 0.00;
  float min_z = 0.00, max_z = 0.00;

  count = 0;
  msg = "Computing GYR Offset ...";
  Serial.println();
  Serial.println(msg);

  while (count < DATA_LENGTH)
  {
    float gxRaw, gyRaw, gzRaw;
    mpu6050_imu.get_gyro_radps(gxRaw, gyRaw, gzRaw);

    max_x = max(gxRaw, max_x);
    min_x = min(gxRaw, min_x);

    max_y = max(gyRaw, max_y);
    min_y = min(gyRaw, min_y);

    max_z = max(gzRaw, max_z);
    min_z = min(gzRaw, min_z);

    // Serial.print(count);
    count += 1;

    delay(10);
  }

  gxOff = (max_x + min_x) / 2.00;
  gyOff = (max_y + min_y) / 2.00;
  gzOff = (max_z + min_z) / 2.00;

  msg = "GYR Offset: [" + String(gxOff, 6) + "," + String(gyOff, 6) + "," + String(gzOff, 6) + "]";
  Serial.println(msg);
}

void setup()
{
  /* Serial to display data */
  Serial.begin(115200);

  mpu6050_imu.init(); // with 12c address 0x68

  delay(3000);

  // calibrateAccGyr();
  readImuTime = millis();
}

void loop()
{
  readCalAccGyr();
}