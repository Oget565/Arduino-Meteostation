# Arduino Clock and Weather Station
[![Static Badge](https://img.shields.io/badge/My_Website-green?link=https%3A%2F%2Foget565.com%2F)](https://oget565.com/) [![YouTube](https://img.shields.io/badge/YouTube-color?color=%23FF0000&link=https%3A%2F%2Fwww.youtube.com%2F%40oget565)](https://www.youtube.com/@oget565) [![Static Badge](https://img.shields.io/badge/Twitch-color?color=%239146FF&link=https%3A%2F%2Fwww.twitch.tv%2Foget565)](https://www.twitch.tv/oget565)





This project will include everything to create a weather station for your home.

Status: Ready, There is a STL case file, but no back lid YET.

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
### BME280 
VIN →	 5V

GND →	 GND

SCL →	 A5

SDA →	 A4

### ENS160
VIN →	 5V

GND →	 GND

SCL →	 A5

SDA →	 A4

### TFT DISPLAY
VCC →	5V

GND →	 GND

SCL →	 D13

SDA →	 D11

RES →	 D8

DC →	 D9

CS →	 D10

### DS3231
VCC → 5V

GND →	 GND

SCL →	 A5

SDA A4

2) Download these libraries:
   -  RTClib
   -  Adafruit_GFX
   -  Adafruit_ST7735
   -  GyverBME280
   -  SparkFun_ENS160
   -  Forecaster

3) Upload the code
4) Done!

## How to use?

- Time section: Displays time and date
- Temperature and humidity section: Displays current temperature in Celsius. Humidity is displayed in light blue text with the percentage
- The AQI section displays the current AQI (1—lowest, the best | 5—highest, the worst). It also shows the current Co2 and EtOh concentrations in ppm.
- Rain prediction section: It actually displays the percentage of weather getting worse (0 to 100%). If it stays below ~20%, weather probably won't change. It uses BME280's pressure and Zambretti algorithm to predict. Please allow at least 3 hours after the powering to get accurate results. Note that data won't be saved after the powering off.
