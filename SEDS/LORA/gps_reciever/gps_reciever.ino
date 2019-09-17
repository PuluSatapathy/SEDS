#include <SoftwareSerial.h>
#include<TinyGPS.h>
SoftwareSerial GPSModule(10, 11); // RX, TX
SoftwareSerial hc12(4, 5);


void setup() {
 Serial.begin(9600);
  GPSModule.begin(9600);
  hc12.begin(9600);

}

void loop() {
  if (hc12.available())
  {
    data=hc12.parseInt();
    Serial.println(data);
  }

}
