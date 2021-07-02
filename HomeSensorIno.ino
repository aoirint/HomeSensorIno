// requires
// - ArduinoJson
// - DHT sensor library by Adafruit

#include <ArduinoJson.h>
#include <DHT.h>
#include "MHZ19.h"
#include <SoftwareSerial.h>

#define BAUDRATE 38400
#define PIN_DHT 3    // DHT11
#define PIN_PHOTO A0 // フォトトランジスタ
#define PIN_MHZ_TX 4 // Arduino Tx -- MHZ19 Rx
#define PIN_MHZ_RX 5 // Arduino Rx -- MHZ19 Tx
#define BAUDRATE_MHZ 9600

DHT dht(PIN_DHT, DHT11);

MHZ19 mhz19;
SoftwareSerial mhz19Serial(PIN_MHZ_RX, PIN_MHZ_TX);

StaticJsonDocument<128> serialJson;
DynamicJsonDocument data(128);

void setup() {
  pinMode(PIN_PHOTO, INPUT);

  Serial.begin(BAUDRATE);
  dht.begin();
  
  mhz19Serial.begin(BAUDRATE_MHZ);
  mhz19.begin(mhz19Serial);

  mhz19.autoCalibration();
}

void loop() {
  writeSerial();

  bool jsonError = false;

  serialJson.clear();
  data.clear();

  if (nextSerialJson(&serialJson, &jsonError)) {
    String type = serialJson["type"];

    if (type.equals("null")) {
    }
  }
  else if (jsonError) {
    data["type"] = "jsonError";
    serializeJson(data, Serial);
    Serial.println("");
  }

}

void writeSerial() {
  int light = analogRead(PIN_PHOTO);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  int mhz19Co2 = mhz19.getCO2();
  int8_t mhz19Temperature = mhz19.getTemperature();

  data.clear();
  data["type"] = "sensor";
  data["light"] = light;
  data["humidity"] = humidity;
  data["temperature"] = temperature;
  data["mhz19_co2"] = mhz19Co2;
  data["mhz19_temperature"] = mhz19Temperature;
  serializeJson(data, Serial);
  Serial.println("");
}

