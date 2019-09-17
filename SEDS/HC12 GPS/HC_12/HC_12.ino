#include <SoftwareSerial.h>

SoftwareSerial HC12(11,12);     // SoftwareSerial(RX,TX)

int set=3;    //set pin GND this pin to enable AT Command mode
char ch;
String mesg="";

void setup() {
 
  Serial.begin(9600);
  HC12.begin(9600);
}

void loop() {
 
  while(HC12.available())          //reading data from HC-12 to the serial monitor
  {
    ch=char(HC12.read());
    mesg=mesg+ch;
  }
  if(mesg!=""){
  Serial.print("Recieved messege: ");
    Serial.println(mesg);
    mesg="";
}
}
