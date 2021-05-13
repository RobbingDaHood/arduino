#include <ESP8266WiFi.h>
#include <Pinger.h>

// Set global to avoid object removing after setup() routine
Pinger pinger;

void setup () {

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  WiFi.begin("YaxuansNetwork", "InternetNow");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connections status: " + WiFi.status());
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(pinger.Ping("192.168.1.168") ? "Pinged" : "Not Pinged");
  }

  delay(1000);    //Send a request every 1 second
}
