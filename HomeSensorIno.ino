// requires
// - ArduinoJson
// - DHT sensor library by Adafruit

#include <ArduinoJson.h>
#include <DHT.h>

#define BAUDRATE 38400
#define PIN_DHT 3    // DHT11
#define PIN_PHOTO A0 // フォトトランジスタ

DHT dht(PIN_DHT, DHT11);

StaticJsonDocument<128> serialJson;
DynamicJsonDocument data(128);

void setup() {
  pinMode(PIN_PHOTO, INPUT);

  Serial.begin(BAUDRATE);
  dht.begin();
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

  data.clear();
  data["type"] = "sensor";
  data["light"] = light;
  data["humidity"] = humidity;
  data["temperature"] = temperature;
  data["temperature"] = temperature;
  serializeJson(data, Serial);
  Serial.println("");
}

