
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
//FC:F5:C4:0A:0D:FA

#define SERVICE_UUID        "44afc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  
  //Then, you create a BLE device called “MyESP32”. You can change this name to whatever you like.
  BLEDevice::init("Milad");
  
  //In the following line, you set the BLE device as a server.
  BLEServer *pServer = BLEDevice::createServer();
  
  //After that, you create a service for the BLE server with the UUID defined earlier.
  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

 
  //After creating the characteristic, you can set its value with the setValue() method.
  //In future projects, this text can be a sensor reading, or the state of a lamp, for example.

  
  //pCharacteristic->setValue("Kushagra says Neil");
  std::string value = pCharacteristic->getValue();
  Serial.println(value.c_str());
  
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  //Finally, you can start the service, and the advertising, so other BLE devices can scan and find this BLE device.
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

}

void loop() {
    BLEDevice::init("Milad");
  
  //In the following line, you set the BLE device as a server.
  BLEServer *pServer = BLEDevice::createServer();
  
  //After that, you create a service for the BLE server with the UUID defined earlier.
  BLEService *pService = pServer->createService(SERVICE_UUID);

  /*
   * Then, you set the characteristic for that service. As you can see, you also use the UUID defined earlier,
   *  and you need to pass as arguments the characteristic’s properties. In this case, it’s: READ and WRITE.
  */
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

 
  //After creating the characteristic, you can set its value with the setValue() method.
  //In future projects, this text can be a sensor reading, or the state of a lamp, for example.
  //pCharacteristic->setValue("Kushagra says Neil");
  std::string value = pCharacteristic->getValue();
  Serial.println("__________");
  Serial.println(value.c_str());
  delay(2000);
}
