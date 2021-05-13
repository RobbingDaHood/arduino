#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YaxuansNetwork";
const char* password = "InternetNow";
const char* address = "http://192.168.1.168:1880/humtemp";
const char* contentTypeHeader = "Content-Type";
const char* contentTypeHeaderValue = "application/json";
const String deviceName = "HumTemp1";
const int oneSecond = 1000;
const int thirtyMinutes = 1800000;
const int createdCode = 201;
const int baudRateValue = 115200;

void setup () {
  Serial.begin(baudRateValue);
  //Serial.setDebugOutput(true);
}

void loop() {
  Serial.println("loop");
  connectToWifi();
  sendData(getData());
  lightSleep();
  Serial.println("endloop");
}

void sendData(String data) {
  HTTPClient http;  //Declare an object of class HTTPClient

  Serial.print("http.begin(address): ");
  Serial.println(http.begin(address));

  Serial.println("http.addHeader(contentTypeHeader, contentTypeHeaderValue): ");
  http.addHeader(contentTypeHeader, contentTypeHeaderValue);

  int httpCode;
  int count = 0;
  while (httpCode != createdCode) {
    Serial.print("Count: ");
    Serial.println(count++);
    Serial.print("http.POST(data): ");
    httpCode = http.POST(data);
    Serial.println(httpCode);
    delay(oneSecond);
  }

  http.end();   //Close connection
}

String getData() {
  Serial.println("dht.begin(): ");
  dht.begin();

  while (true) {
    Serial.print("hdht.readTemperature()");
    float temp = dht.readTemperature();
    if (isnan(temp)) {
      Serial.println("Failed to read temp from DHT sensor!");
      delay(oneSecond);
      continue;
    }
    Serial.println(temp);

    Serial.print("hdht.readHumidity()");
    float hum = dht.readHumidity();
    if (isnan(hum)) {
      Serial.println("Failed to read humemp from DHT sensor!");
      delay(oneSecond);
      continue;
    }
    Serial.println(hum);

    String data = "{\"device_name\": \"" + deviceName + "\", \"humidity\": \"" + hum + "\", \"temperature\": \"" + temp + "\"}";
    Serial.print("data: ");
    Serial.println(data);

    return data;
  }
}

void connectToWifi() {
  Serial.println("WiFi.begin(ssid, password)");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connections status: ");
    Serial.println(WiFi.status());
    delay(oneSecond);
  }
  Serial.print("Connected");
}

void lightSleep() {
  Serial.println("I'm awake, but I'm going into deep sleep mode for 30 minutes");
  uint32_t sleep_time_in_ms = 10000;
  wifi_set_opmode(NULL_MODE);
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_do_sleep(thirtyMinutes * 1000 );
  delay(thirtyMinutes + 1);
  Serial.println("I'm am waking up");
  wifi_set_sleep_type(NONE_SLEEP_T);
}
