const int ledPin = 16;  // 16 corresponds to GPIO16
uint16_t dutyCycle;
// setting PWM properties
const int freq = 15000;
const int ledChannel = 0;
const int resolution = 13;


void setup(){

  
  Serial.begin(9600);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  
}
void loop(){

   dutyCycle =  analogRead(A0); 
   Serial.print(dutyCycle);
   // changing the LED brightness with PWM
   ledcWrite(ledChannel, dutyCycle);
   delay(15);
  }
