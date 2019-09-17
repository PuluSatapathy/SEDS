#include <SoftwareSerial.h>
SoftwareSerial hc12(2,3);
//boolean ONOFF = 0;    
void setup() {
    Serial.begin(9600);
    hc12.begin(9600);
}

void loop() {
  if(Serial.available() > 1){
    String input = Serial.readString();
    hc12.println(input);
    //ONOFF==1;    
  }
  delay(20);
}
