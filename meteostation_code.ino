#include "Wire.h"
#include "math.h"
#include "RTClib.h"
#include "Adafruit_GFX.h"
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include "Adafruit_ST7735.h"
#include "GyverBME280.h"
#include "SparkFun_ENS160.h"
#include "Forecaster.h"

GyverBME280 bme;

Forecaster cond;

SparkFun_ENS160 myENS;
int ensStatus;  

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(57600);
  Wire.begin();

  	if( !myENS.begin() )
	{
		Serial.println("Could not communicate with the ENS160, check wiring.");
		while(1);
	}

  Serial.println("Example 1 Basic Example.");

	// Reset the indoor air quality sensor's settings.
	if( myENS.setOperatingMode(SFE_ENS160_RESET) )
		Serial.println("Ready.");

	delay(100);

	// Device needs to be set to idle to apply any settings.
	// myENS.setOperatingMode(SFE_ENS160_IDLE);

	// Set to standard operation
	// Others include SFE_ENS160_DEEP_SLEEP and SFE_ENS160_IDLE
	myENS.setOperatingMode(SFE_ENS160_STANDARD);

	// There are four values here: 
	// 0 - Operating ok: Standard Operation
	// 1 - Warm-up: occurs for 3 minutes after power-on.
	// 2 - Initial Start-up: Occurs for the first hour of operation.
  //												and only once in sensor's lifetime.
	// 3 - No Valid Output
	ensStatus = myENS.getFlags();
	Serial.print("Gas Sensor Status Flag (0 - Standard, 1 - Warm up, 2 - Initial Start Up): ");
	Serial.println(ensStatus);

  //SCREEN 
  tft.initR(INITR_GREENTAB);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);

  //CLOCK
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //BME280
  bme.setFilter(FILTER_COEF_8);                     // Настраиваем коофициент фильтрации
  bme.setTempOversampling(OVERSAMPLING_8);          // Настраиваем передискретизацию для датчика температуры
  bme.setPressOversampling(OVERSAMPLING_16);        // Настраиваем передискретизацию для датчика давления
  bme.setStandbyTime(STANDBY_500MS);                // Устанавливаем время сна между измерениями (у нас обычный циклический режим)
  bme.begin(); 	

  //Forecaster
  cond.setH(204);

}

void loop() {
  #define ST7735_RGB  // RGB order
  uint16_t lightBlue = tft.color565(252, 243, 63);
  uint16_t aqiColor = tft.color565(94, 255, 0);
  uint16_t coColor = tft.color565(45, 45, 250);
  uint16_t etohColor = tft.color565(120, 190, 191);
  uint16_t rainColor = tft.color565(255, 38, 56);
  DateTime now = rtc.now();

  //TIME
  int hour = now.hour();
  bool isPM = false;

  if (hour == 0) {
    hour = 12; // Midnight
  } else if (hour == 12) {
    isPM = true; // Noon
  } else if (hour > 12) {
    hour -= 12;
    isPM = true; // PM
  }

  tft.fillRect(0, 0, 200, 200, ST77XX_BLACK);
  tft.drawLine(0, 60, 160, 60, ST77XX_WHITE);
  tft.drawLine(100, 0, 100, 60, ST77XX_WHITE);
  tft.drawLine(90, 60, 90, 128, ST77XX_WHITE);

  //TIME SCREEN SECTION
  tft.setFont(&FreeSansBold12pt7b);
  tft.setCursor(1,20);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(hour);
  tft.print(':');
  if (now.minute() < 10) Serial.print("0");
  tft.print(now.minute());
  tft.print(isPM ? "PM" : "AM");
  tft.setCursor(1, 37);
  tft.setFont(&FreeSansBold9pt7b);
  tft.print(now.month());
  tft.print('/');
  tft.print(now.day());
  tft.print('/');
  tft.print(now.year());
  tft.setCursor(1,53);
  tft.print(daysOfTheWeek[now.dayOfTheWeek()]);

  //TEMP SCREEN SECTION
  int tempz = ceil(bme.readTemperature());
  int humz = ceil(bme.readHumidity());

  tft.setFont(&FreeSansBold12pt7b);
  tft.setCursor(106,25);
  tft.print(tempz);
  tft.print(" C");
  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(116, 50);
  tft.setTextColor(lightBlue);
  tft.print(humz);
  tft.print("%");

  //AQI SCREEN SECTION
  tft.setFont(&FreeSansBold12pt7b);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(1,85);
  tft.setTextColor(aqiColor);
  tft.print("AQI:");
  tft.print(myENS.getAQI());
  tft.setFont(&FreeSansBold9pt7b);
  tft.setTextColor(coColor);
  tft.setCursor(1,103);
  tft.print("CO2:");
  tft.print(myENS.getECO2());
  tft.setTextColor(etohColor);
  tft.setCursor(1,121);
  tft.print("ETOH:");
  tft.print(myENS.getETOH());
  
  //RAIN SCREEN SECTION
  tft.setCursor(95,85);
  tft.setTextColor (rainColor);
  tft.setFont(&FreeSansBold12pt7b);
  tft.print("Rain:");
  static uint32_t tmr;
  if (millis() - tmr >= 30*60*1000ul) {
    tmr = millis();
    cond.addP(bme.readPressure(), bme.readTemperature());
  }
    int rain = cond.getCast() * 100 / 10;

    tft.setCursor(110,115);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(rain);
    tft.print("%");

  delay(60000);
}
