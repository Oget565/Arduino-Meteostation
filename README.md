# Arduino Clock and Weather Station
This project will include everything to create a weather station for your home.

Status: Ready, but no 3d print STL case file

## Features:
- Basic clock
- Shows temperature and humidity
- Show AQI, eCO2, and EtOH
- Able to predict weather change based on pressure change.
- Color display

## Components:
1) Arduino Nano
2) 128 x 160 TFT LCD Screen (ST7735)
3) DS3231
4) BME280
5) ENS160 + AHT21
8) Type C power connector

## Instructions:

1) Connect modules to arduino:

| Module    | Pin      | Arduino pin                |
| :--------: | :-------: | :-------------------------: |
| BME280 | VIN | 5V|
|  | GND | GND| 
| | SCL | A5|
| | SDA | A4|
| ENS160 | VIN | 5V|
| | GND | GND |
| | SCL | A5 |
| | SDA | A$ |
| TFT DISPLAY | VCC | 5V |
| | GND | GND |
| | SCL | D13| 
| | SDA | D11 |
| | RES | D8 |
| | DC | D9 |
| | CS | D10|
| DS3231 | VCC | 5V|
| | GND | GND |
| | SCL | A5 |
| | SDA | A4 |

2) Download these libraries:
   -  RTClib
   -  Adafruit_GFX
   -  Adafruit_ST7735
   -  GyverBME280
   -  SparkFun_ENS160
   -  Forecaster

3) Upload the code
4) Done!
