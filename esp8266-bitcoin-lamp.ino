#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const int RED = 15;
const int GREEN = 12;

StaticJsonBuffer<10240> jsonBuffer;
WiFiClientSecure client;
String response = "";

void setup() {

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  // Start the serial port
  Serial.begin(2000000);
  Serial.println();
  Serial.println("ESP8266 BitCoin lamp will start");
  Serial.setDebugOutput(true);

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin("Volya", "SocSocovich");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("*");
  }

  Serial.println();
  Serial.println("Connected to WiFi:");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

void loop() {
  
  if (!client.connected()) {

    if (0 < response.length()) {

      // Trim the response header
      int headerEndPosition = response.indexOf("\r\n\r\n");
      response = response.substring(headerEndPosition + 4);
      Serial.println("HTTP response:");
      Serial.println(response);

      // Parse the JSON response
      JsonArray& jsonResponse = jsonBuffer.parseArray(response);
      if(jsonResponse.success()) {
        JsonObject& jsonTicker = jsonResponse[0];
        String changePercentageString = jsonTicker["percent_change_24h"];
        Serial.println("Price change percentage:");
        Serial.println(changePercentageString);
        float changePercentage = changePercentageString.toFloat();
        if (0 < changePercentage) {
            analogWrite(GREEN, changePercentage);
        } else {
            analogWrite(RED, -changePercentage);
        }
      }

      delay(60 * 1000);
      
      response = "";
    }

    // Connect to the Web server
    if (client.connect("api.coinmarketcap.com", 443)) {
      Serial.println("Connected to Web server");
      client.println("GET /v1/ticker/?limit=1 HTTP/1.1");
      client.println("Host: api.coinmarketcap.com");
      client.println("Connection: close");
      client.println();
    }  
  }

  while (client.available()) {
    char c = client.read();
    response += c;
  }  
}
