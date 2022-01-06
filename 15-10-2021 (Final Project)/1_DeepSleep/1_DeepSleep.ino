//   IOT Group 3
//   Milad ZAHEDIYAMI
//   KushagraSingh BISEN  

//After 5 seconds of inactivity, the microcontroller falls into deep sleep.


/* Conversion factor for mili seconds to seconds */
#define uS_TO_S_FACTOR 1000  

/* Time ESP32 will go to sleep (in seconds) */
#define TIME_TO_SLEEP  5        

void setup() {
  
    Serial.begin(115200);
    //After 5 seconds of inactivity, 
    //the microcontroller falls into deep sleep.
    
    delay(TIME_TO_SLEEP*uS_TO_S_FACTOR);
    
    esp_deep_sleep_start();
    
    Serial.println("This will never be printed");
}

void loop() {
  
}
