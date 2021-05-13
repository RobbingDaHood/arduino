#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YaxuansNetwork";
const char* password = "InternetNow";
const char* address = "http://192.168.1.168:1880/humtemp";
const char* contentTypeHeader = "Content-Type";
const char* contentTypeHeaderValue = "application/json";
const char* data = "{\"device_name\": \"ESP8266Test\", \"humidity\": \"2.2\", \"temperature\": \"3.3\"}";
const int oneSecond = 1000;
const int thirtyMinutes = 1800000;
const int createdCode = 201;
const int baudRateValue = 115200;

int count = 0;

void setup () {
  Serial.begin(baudRateValue);
  //Serial.setDebugOutput(true);

  Serial.println("WiFi.begin(ssid, password)");
  WiFi.begin(ssid, password);
  //delay(oneSecond);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connections status: ");
    Serial.println(WiFi.status());
    delay(oneSecond);
  }
}

void loop() {

  Serial.println("loop: WiFi.status()");
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    Serial.print("http.begin(address): ");
    Serial.println(http.begin(address));
    //delay(oneSecond);

    Serial.println("http.addHeader(contentTypeHeader, contentTypeHeaderValue);");
    http.addHeader(contentTypeHeader, contentTypeHeaderValue);
    //delay(oneSecond);

    int httpCode;
    //while (httpCode != createdCode) {
      Serial.print("Count: ");
      Serial.println(count++);
      Serial.print("http.POST(data): ");
      httpCode = http.POST(data);
      Serial.println(httpCode);
      //delay(oneSecond);
    //}

    Serial.print("http.getString(): ");
    Serial.println(http.getString());

    http.end();   //Close connection

  }

  Serial.println("endloop");
  delay(thirtyMinutes);    //Send a request every 5 seconds
}
