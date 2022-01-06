#include "WiFi.h"
#include "HTTPClient.h"

const char* ssid = "NETGEAR95";
const char* password = "purpleunicorn212";
String serverName = "http://192.168.1.149/api/6XM076EpSB9C92pV1GMFwGUaGcqnfanKrlOe0RQn/lights/1/state";

void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}



void loop() {
 
 if(WiFi.status()== WL_CONNECTED){
 
   HTTPClient http;   
 
   http.begin(serverName);
   http.addHeader("Content-Type", "application/json");            

   
   int httpResponseCode = http.PUT("{\"on\":true, \"sat\":100, \"bri\":100, \"hue\":10000}");   
 
   if(httpResponseCode>0){
 
    String response = http.getString();   
 
    Serial.println(httpResponseCode);
    Serial.println(response);          
 
   }else{
 
    Serial.print("Error on sending PUT Request: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();
 
 }else{
    Serial.println("Error in WiFi connection");
 }
 
  delay(10000);
}
