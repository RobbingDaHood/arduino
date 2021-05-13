#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  Serial.println("WiFi.begin " + WiFi.begin("YaxuansNetwork", "InternetNow"));

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println();
    Serial.print("Connection status: ");
    Serial.println(WiFi.status());

    WiFi.printDiag(Serial);
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
