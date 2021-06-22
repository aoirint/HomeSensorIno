
// requires
// - DHT sensor library by Adafruit
// - IRremote

#include <ArduinoJson.h>
#include <DHT.h>

// #include <boarddefs.h>
// #include <IRremote.h>
// #include <IRremoteInt.h>
// #include <ir_Lego_PF_BitStreamEncoder.h>


#define BAUDRATE 38400
#define PIN_DHT 3    // DHT11
#define PIN_PHOTO A0 // フォトトランジスタ

DHT dht(PIN_DHT, DHT11);

// IRsend irsend;

StaticJsonDocument<128> serialJson;
DynamicJsonDocument data(128);

void setup() {
  pinMode(PIN_PHOTO, INPUT);

  Serial.begin(BAUDRATE);
  dht.begin();
}

void loop() {
  writeSerial();

  // {"type":"ac","cmd":"cool28"}
  bool jsonError = false;

  serialJson.clear();
  data.clear();

  if (nextSerialJson(&serialJson, &jsonError)) {
    String type = serialJson["type"];

    if (type.equals("null")) {
    }
    // else if (type.equals("ac")) {
    //   String cmd = serialJson["cmd"];
    //   String msg = "xxx";
    //
    //   bool ret = sendIR(cmd, &msg);
    //
    //   data["ret"] = ret;
    //   data["msg"] = msg;
    //
    //   serializeJson(data, Serial);
    //   Serial.println("");
    // }
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
  serializeJson(data, Serial);
  Serial.println("");
}
