#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YaxuansNetwork";
const char* password = "InternetNow";
const char* getAdress = "http://192.168.1.168:1880/humtemp";


void setup () {

  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connections status: ");
    Serial.println(WiFi.status());
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    Serial.print("http.begin(getAdress): ");
    Serial.println(http.begin(getAdress));
    int httpCode = http.GET();
    Serial.print("http.GET(): ");
    Serial.println(httpCode);

    while (httpCode != 200) {
      delay(1000);    //Send a request every 5 seconds
      httpCode = http.GET();                                  //Send the request
      Serial.print("http.GET(): ");
      Serial.println(httpCode);
    }

    Serial.println(http.getString());             //Print the response payload

    http.end();   //Close connection

  }

  delay(5000);    //Send a request every 5 seconds
}
