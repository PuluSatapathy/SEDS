#include<SoftwareSerial.h>
SoftwareSerial hc12(2,3);
int ledPin = 13;
boolean current;
boolean last=LOW;
int lastip;
void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  int input;
    if(hc12.available()) 
 {
  input=hc12.parseInt();
  delay(100);
 }
  Serial.println(input);
    if(input==1) 
    current=!last;
    else 
    last=current;
    digitalWrite(LED_BUILTIN,current);
}
