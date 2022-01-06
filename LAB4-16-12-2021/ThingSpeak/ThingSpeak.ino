#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "NETGEAR95";   // your network SSID (name) 
const char* password = "purpleunicorn212";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "QJXAAVDVP0ZUMQ8A";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

// Variable to hold temperature readings
String on   = "true";
int sat = 100;
int hue = 100;
int bri = 10000;


void setup() {
  Serial.begin(115200);  //Initialize serial

  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // set the fields with the values
    ThingSpeak.setField(1, on);
    ThingSpeak.setField(2, sat);
    ThingSpeak.setField(3, hue);
    ThingSpeak.setField(4, bri);
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
