//To Distance
/*
by：bilibilifmk
mcu：air001
开发环境sdk：https://wiki.luatos.com/chips/air001/Air001-Arduino.html
*/


#include <EEPROM.h>
#include <Wire.h>
#include "VL53L1X.h"

VL53L1X sensor;
int mode = 0;
#include "evilOLED.h"

evilOLED disp(PA7, PA5);


void setup() {


  EEPROM.get(0, mode);
  if (mode > 3 || mode < 0)
  {
    mode = 0;
    EEPROM.put(0, mode);
    delay(10);
  }
  pinMode(PA7, OUTPUT);
  pinMode(PA5, OUTPUT);

  evilOLED disp(PA7, PA5);

  Serial.begin(115200);
  Serial.println(mode);
  Wire.begin();
  Wire.setClock(400000);
  sensor.setTimeout(500);

  if (!sensor.init())
  {
  
    disp.cls(0x00);
    disp.setCursor(0, 0);
    disp.putString("SENSOR LINK");
    disp.setCursor(0, 1);
    disp.putString("I2C ERROR");
    disp.setCursor(0, 2);
    disp.putString("CHECK LINK");
    while (1);
  }

  sensor.init();

  if (mode == 0)
  {
    sensor.setDistanceMode(VL53L1X::Short);
    sensor.setMeasurementTimingBudget(50000);
    sensor.startContinuous(50);
    int buf = 1;
    EEPROM.put(0, buf);
  } else if (mode == 1)
  {
    sensor.setDistanceMode(VL53L1X::Medium);
    sensor.setMeasurementTimingBudget(50000);
    sensor.startContinuous(100);
    int buf = 2;
    EEPROM.put(0, buf);
  } else if (mode == 2)
  {
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);
    sensor.startContinuous(200);
    int buf = 0;
    EEPROM.put(0, buf);
  }

  //delay(200);
  init_dp();
}

void loop() {

  tof_dp();
  delay(100);
}


void tof_dp()
{
  VL53L1X sensor;

  sensor.read();

  //  Serial.print("range: ");
  //  Serial.print(sensor.ranging_data.range_mm);
  //  Serial.print("\tstatus: ");
  //  Serial.print(VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
  //  Serial.print("\tpeak signal: ");
  //  Serial.print(sensor.ranging_data.peak_signal_count_rate_MCPS);
  //  Serial.print("\tambient: ");
  //  Serial.print(sensor.ranging_data.ambient_count_rate_MCPS);
  //  Serial.println();

  disp.setCursor(7, 4);
  disp.putString(sensor.ranging_data.range_mm);
  disp.putString(" MM   ");
  String status_buf = VL53L1X::rangeStatusToString(sensor.ranging_data.range_status);
  int range = sensor.ranging_data.range_mm;
  Serial.println(status_buf);




  disp.setCursor(3, 7);
  if (status_buf == "n1")
  {
    disp.putString("    LOW TRUST");
  }
  else if (status_buf == "ok")
  {
    disp.putString("    STATE OK ");
  }
  else
  {
    disp.putString("   GET ERROR ");
  }


}

void init_dp()
{
  disp.cls(0x00);
  disp.setCursor(0, 0);
  disp.putString("MODE TOF RANGING");
  disp.setCursor(1, 2);
  disp.putString("S");
  disp.setCursor(1, 4);
  disp.putString("M");
  disp.setCursor(1, 6);
  disp.putString("L");
  if (mode == 0)
  {
    disp.setCursor(3, 2);
    disp.putString("X");
    disp.setCursor(3, 4);
    disp.putString(" ");
    disp.setCursor(3, 6);
    disp.putString(" ");
  }
  else if (mode == 1)
  {
    disp.setCursor(3, 2);
    disp.putString(" ");
    disp.setCursor(3, 4);
    disp.putString("X");
    disp.setCursor(3, 6);
    disp.putString(" ");
  } else if (mode == 2)
  {
    disp.setCursor(3, 2);
    disp.putString(" ");
    disp.setCursor(3, 4);
    disp.putString(" ");
    disp.setCursor(3, 6);
    disp.putString("X");
  }
  //  delay(1000);
}
