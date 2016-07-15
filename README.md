# linux-mpu6050-driver
Linux MPU6050 Driver **Work in Progress**
====================

Im writing this driver to learn about driver programming for linux. Im using a raspberry pi as the development platform. This driver may not be complete. At present it detects the presence of MPU6050. I have connected the sensor to i2c bus and it shows up in address 0x68.

Usage
------
You need to have the proper kernel headers installed to build this driver. Use this tool to install kernel headers https://github.com/notro/rpi-source

1. clone this repo 
2. git clone linux-mpu6050-driver
3. cd into directory
4. type make
5. sudo insmod mpu6050.ko
6. type lsmod and see whether the driver is loaded properly
7. sudo bash
8. if you have a new Raspberry pi (B+, 2 or 3)

  echo mpu6050 0x68 > /sys/class/i2c-adapter/i2c-1/new_device

  else if this is a Rev. 1

  echo mpu6050 0x68 > /sys/class/i2c-adapter/i2c-0/new_device

  Type dmesg and check if it shows any error messages



TODO
-----
1. Write several routines to read data
2. Create a FS node in /dev directory to read sensor values
