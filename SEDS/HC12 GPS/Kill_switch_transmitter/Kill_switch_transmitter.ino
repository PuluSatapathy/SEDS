//-----------------------------Transmitter-----------------------------
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
//                                      GPS (need an accuracy of 0.00001degrees)
static const int RXPin =10 , TXPin = 9;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

SoftwareSerial HC12(11,12);     // SoftwareSerial(RX,TX)

int set=3;    //set pin GND this pin to enable AT Command mode
char ch;
String mesg="";

void setup() {
 
  Serial.begin(9600);
  HC12.begin(9600);
   ss.begin(9600);
}

void loop() {
  
  //-------------------------------Waiting for the GPS to respond--------
   while(!(gps.location.isValid() && gps.location.isUpdated()))
     { 
      if (millis() > 5000 && gps.charsProcessed() < 10){
          Serial.println(F("No GPS data received: check wiring"));
          HC12.print("No GPS data received: check wiring");}
      Serial.println("waiting for the GPS coordinates");
      HC12.print("waiting for the GPS coordinates");
      smartDelay(500);
     }
//-------------------------------Getting the GPS coordinates-----------
      Serial.println("GPS ready");
      double lat1=gps.location.lat();
      Serial.print("lattitude=");
      Serial.println(lat1);
      double lon1=gps.location.lng();
      Serial.print("longitude=");
      Serial.println(lon1);
//------------------------------transmission----------------------------
    String latt=String(lat1);
    String lonn=String(lat1);
    mesg=latt+" "+lonn;
    HC12.print(mesg);
}
void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
