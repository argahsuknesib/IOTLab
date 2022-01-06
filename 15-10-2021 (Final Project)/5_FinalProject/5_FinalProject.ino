//   IOT Group 3
//   Milad ZAHEDIYAMI
//   KushagraSingh BISEN  

//Menu options are: 
//1. display temperature and humidity, 
//2. change temperature F°/C°, 
//3. turn the light on/off, 
//4. change potentiometer action: dim/set color, 
//5. sleep.

//Menu options can be selected using the pink button.


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

//dht
#include "DHT.h"
#define DHTPIN 15     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);


const int PushButton = 33;
RTC_DATA_ATTR int bootCount = 0;

//Potentiometer
int potPin = 21;    // select the input pin for the potentiometer


void setModemSleep();
void wakeModemSleep();

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low

  if(bootCount==0){  
    ++bootCount;
    //Go to sleep now
    Serial.println("Going to sleep now");
    esp_deep_sleep_start();
    Serial.println("This will never be printed");  
  }

  //DHT
  Serial.println(F("DHTxx test!"));
  dht.begin();

  Serial.println("128x64 OLED FeatherWing test");
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  Serial.println("Button test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,22);
  display.println("     PRESS BUTTON     ");
  display.println("    TO START MENUE    ");

 // display.display(); // actually display all of the above

  

}


int state = 0;
int led_counter = 0;

void loop(){
  
  yield();
  display.display();

  int prev = 0;
  int Push_button_state = digitalRead(PushButton);

  //DHT
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


  if( Push_button_state==1 && prev ==0 &&state==0 ){
    
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));
  
    display.clearDisplay();
    display.setCursor(0,10);
    display.println("_____________________");
    display.println("");
    display.print("1.  Temp:     ");
    display.print(t);
    display.println("C ");
    display.print("    Humidity: ");
    display.print(h);
    display.println("%");
    display.println("_____________________");

    prev = Push_button_state;
    state = (state+1)%5;
    delay(1000);
  }  
  
  if( Push_button_state==1 && prev ==0 &&state==1 ){
    display.clearDisplay();
    display.setCursor(0,10);
    display.println("_____________________");
    display.println("");
    display.print("2.  Temp:     ");
    display.print(f);
    display.println("F ");
    display.print("    Humidity: ");
    display.print(h);
    display.println("%");
    display.println("_____________________");

    prev = Push_button_state;
    state = (state+1)%5;
    delay(1000);
  }

  
  if(Push_button_state==1 && prev==0 &&state==2) {
    
    display.clearDisplay();
    display.setCursor(0,0);
    display.setCursor(0,14);
    display.println("_____________________");
    display.println("");
    display.println("3. Turn on/off"); 
    display.println("_____________________");

    
    prev = Push_button_state;
    state = (state+1)%5;
    delay(1000);

    if(led_counter%2==0){
        digitalWrite(LED_BUILTIN, HIGH);
    }else{
        digitalWrite(LED_BUILTIN, LOW);
    }
    led_counter++;

     
  }

  
  if(Push_button_state==1 && prev==0 &&state==3){

      int val = analogRead(potPin);    // read the value from the sensor
      display.clearDisplay();
      display.setCursor(0,0);
      display.setCursor(0,10);
      display.println("_____________________");
      display.println("");
      display.println("4. Potentiometer");
      display.print("   Value: ");
      display.println(val);
      display.println("_____________________");

      Serial.print("Potentiometer Value");
      Serial.println(val);
      prev = Push_button_state; 
      state = (state+1)%5;
      delay(1000);   
  }


  if(Push_button_state==1 && prev==0 &&state==4){
      display.clearDisplay();
      display.setCursor(0,0);
      display.setCursor(0,14);
      display.println("_____________________");
      display.println("");
      display.println("5. Sleep");
      display.println("_____________________");
      prev = Push_button_state;
      state = (state+1)%5;
      delay(1000);
      //esp_deep_sleep_start();
  } 


}