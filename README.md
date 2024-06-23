# arduino_mpu6050
this is a sample code for using MPU6050 with madgwick filter


## How to Use the Code
- Download (by clicking on the green Code button above) or clone the repo into your PC

  > NOTE: it makes use of the [`imu_madgwick_filter`](https://github.com/samuko-things/imu_madgwick_filter) library by samuko-things. Ensure to install it.

- First open and run the calibration code to get the offset values - `axOff`, `ayOff`, `azOff`, `gxOff`, `gyOff`, and `gzOff`

- copy and paste the value the filter code. 

- run the filter code to see the filtered `roll`, `pitch`, and `yaw` readings

- use the sample code in your arduino project as you want.
