#include <SoftwareSerial.h>
#include<TinyGPS.h>
SoftwareSerial GPSModule(10, 11); // RX, TX
SoftwareSerial hc12(4, 5);

TinyGPS gps;

float latitude;
float longitude;

void setup(){
  
  Serial.begin(9600);
  hc12.begin(9600);
  GPSModule.begin(9600);
}
void loop() {
  Serial.flush();
  GPSModule.flush();
  hc12.flush();
  
    while (GPSModule.available() > 0)
    {
      if (gps.encode(GPSModule.read()))// encode gps data
    {
      gps.f_get_position(&latitude , &longitude);
        //Serial.print("Position: ");
        //Serial.print("Latitude:");
        //Serial.print(latitude,6);
        //Serial.print(";");
        //Serial.print("Longitude:");
        //Serial.println(longitude,6);
        String lati = String(latitude, 6);
        String longi = String(longitude, 6);
        char ch[(lati+longi).length()];
        (lati+longi).toCharArray(ch,(lati+longi).length());
        hc12.write(lati+longi);
        //hc12.parseInt(longi );
        delay(1000);

      }
    }

}
