## FINAL PROJECT

### Available Menu Options :
- Display Temperature and Humidity
- Change Temperature (*F/C*)
- Turn the light ON/OFF
- Using Potentiometer to change dim the LED.
- Deep Sleep

-------------------------------------
All of the mentioned options work.
-------------------------------------
First Push-Button wakes up the ESP32
-------------------------------------
Second Push-Button starts the Menu.
-------------------------------------
Menu Options are selected with the Pink Button.
-------------------------------------
On choosing th 5th option, ESP32 goes to sleep by 
uncommenting the last line of code

`//esp_deep_sleep_start();`
-------------------------------------

LED is connected to #GPIO 13
DHT sensor is connected to #GPIO 32
Pink Button is connected to #GPIO 15