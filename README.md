# sic_mpu9250_driver_code
This is a child project of the Samuko IMU Compute for MPU9250 (`sic_mpu9250`) project. It contains the code that is uploaded into `sic_mpu9250_driver module` via an FTDI programmer.


## How to Use the Driver Code
- Ensure you have the Arduino IDE up and running on your PC

- Download (by clicking on the green Code button above) or clone the repo into your PC

  > NOTE: it makes use of the `invensense-imu` library by bolder flight and `arduino_matrix_vector_lab` library by samuko-things and `imu_madgwick_filter` library by samuko-things. But all have been used in a concised way to accomodate the microcontroller code space. The license of the code is GPL3 due to license of the midgwick filter

- Open the sic_mpu9250_driver_code folder

- Then open the `sic_mpu9250_driver_code.ino` or `sic_mpu9250_madgwick_filter` code in your Arduino IDE.

- select the board - `Arduino UNO` - and PORT (for the FTDI programmer). 

- verify and upload the code the code to the `sic_mpu9250_driver module` via FTDI programmer.
