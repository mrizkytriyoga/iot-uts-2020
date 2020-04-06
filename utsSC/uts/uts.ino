#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//auth blynk
char auth[] = "eNKEQ2oTL2Hab_qIFpoy70NYsP9c-WAC";

//wifi
char ssid[] = "OPP";
char pass[] = "12345678a";

#define DHTPIN D5
#define DHTTYPE DHT11



DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


void sendSensor()
{
  int sensorValue = analogRead(PIN_A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, PIN_A0);
}

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  int sensorValue = analogRead(PIN_A0);
  Blynk.run();
  timer.run();
  Serial.print("Nilai Sensor :");
  Serial.println(PIN_A0);
}
