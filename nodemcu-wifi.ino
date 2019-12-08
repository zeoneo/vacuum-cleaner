#include <ESP8266WiFi.h>

WiFiServer server(8080);

IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
//byte ledPin = 16;
byte ledPin = 2;

void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_AP);
 WiFi.softAP("PRAKASH", "1234567890");
 WiFi.softAPConfig(IP, IP, mask);
 
 server.begin();

 pinMode(ledPin, OUTPUT);
 Serial.println();
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}

void loop(void) {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("____NEW_COMMAND_____");
        if (request == "LED_ON") {
          digitalWrite(ledPin, LOW);
          Serial.println("LED is now on.");
        } else if (request == "LED_OFF") {
          digitalWrite(ledPin, HIGH);
          Serial.println("LED is now off.");
        } else {
          Serial.println("Invalid command:");
          Serial.println(request);
        }
         Serial.println("From the station: " + request);
         client.flush();
         Serial.print("Byte sent to the station: ");
         Serial.println(client.println(request + "ca" + "\r"));
         Serial.println("*____COMMAND_COMPLETED____*");
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}

void printWiFiStatus() {
  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
