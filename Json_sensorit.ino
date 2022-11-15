// ArduinoJson by Bemoit
#include <ArduinoJson.h>

//SEED_BMEtest_example


#include "Seeed_BME280.h"
#include <Wire.h>

BME280 bme280;


#include "SparkFun_SCD4x_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD4x
SCD4x mySensor;





void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;


  //Only positive values for 280
  unsigned status;
    
  // start 280
  status = bme280.init();
    
  // start SCD41
  mySensor.begin();

}

void loop() {

  //Timecode in MS
  long time = millis();
  
  //BME20 values in loop to save memory

  float pressure = bme280.getPressure();
  int altitude = bme280.calcAltitude(pressure);

  //SCD41 values
  int CO2 = mySensor.getCO2();
  int temp = mySensor.getTemperature();
  int humidity = mySensor.getHumidity();

  // Allocate the JSON document
  // StaticJsonObject allocates memory on the stack (keel low value)
  StaticJsonDocument<50> doc;

  // Add values in the document
  doc["Time"] = time;
  doc["Pressure"] = pressure;
  doc["Altitude"] = altitude;
  doc["Temperature"] = temp;
  doc["Humidity"] = humidity;
  doc["CO2"] = CO2;
  

  // Generate the minified JSON and send it to the Serial port.
  //
  serializeJson(doc, Serial);


  // Start a new line
  Serial.println();

  delay(2000);
}

