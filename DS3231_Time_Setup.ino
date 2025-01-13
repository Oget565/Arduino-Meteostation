#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Force set the RTC to system time on every upload
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("RTC time set to system time!");
}

void loop() {
  DateTime now = rtc.now();

  int hour = now.hour();
  String period = "AM";
  
  if (hour >= 12) {
    period = "PM";
    if (hour > 12) {
      hour -= 12;  // Convert to 12-hour format
    }
  }
  if (hour == 0) {
    hour = 12; // Midnight is 12 AM
  }

  // Print date and time in AM/PM format
  Serial.print("Date: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" Time: ");
  Serial.print(hour);
  Serial.print(':');
  if (now.minute() < 10) {
    Serial.print('0'); // Leading zero for minutes
  }
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.print(' ');
  Serial.println(period);

  delay(1000);
}
