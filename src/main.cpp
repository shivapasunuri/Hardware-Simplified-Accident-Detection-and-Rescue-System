#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <math.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

const int x_out = A1;
const int y_out = A2;
const int z_out = A3;

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void loop()
{
  int y_adc_value, z_adc_value;
  double y_g_value, z_g_value;
  double roll;
  y_adc_value = analogRead(y_out);
  z_adc_value = analogRead(z_out);

  // x_g_value = ((((double)(x_adc_value * 5) / 1024) - 1.65) / 0.330);
  y_g_value = ((((double)(y_adc_value * 5) / 1024) - 1.65) / 0.330);
  z_g_value = ((((double)(z_adc_value * 5) / 1024) - 1.80) / 0.330);

  roll = (((atan2(y_g_value, z_g_value) * 180) / 3.14) + 180);
  // Serial.println(roll);
  // delay(1000);
  if (roll < 20)
  {
    while (ss.available() > 0)
    {
      gps.encode(ss.read());
      if (gps.location.isUpdated())
      {
        Serial.print("https://maps.google.com/maps/?q=");
        Serial.print(gps.location.lat(), 6);
        Serial.print(",");
        Serial.println(gps.location.lng(), 6);
        delay(1000);
      }
    }
  }
}