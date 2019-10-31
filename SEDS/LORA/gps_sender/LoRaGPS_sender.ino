#include <SPI.h>
#include <RH_RF95.h>

#define GPS_PORT Serial

#include "GPS.h"

RH_RF95 rf95;

void setup() 
{
  GPS_PORT.begin(9600);  
  while (!GPS_PORT) ; // Wait for serial port to be available
  
  // send configuration data in UBX protocol
  for(uint8_t i=0; i<sizeof(UBLOX_INIT); i++) {                        
    GPS_PORT.write(pgm_read_byte(UBLOX_INIT+i));
    delay(5); //simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
  }
  
  rf95.init();
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    rf95.setFrequency(433.64);
    rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096);


  uint8_t data[] = "Sender started";
  rf95.send(data, sizeof(data));  
  rf95.waitPacketSent();
}

void loop()
{
  static unsigned long lastSendTime = 0;

  unsigned long now = millis();

  bool gotGPS = false;
  while ( processGPS() ) {
    gotGPS = true;
  }

  if ( gotGPS && now - lastSendTime > 1000 ) {    
    rf95.send((uint8_t*)&loc, sizeof(loc));
    rf95.waitPacketSent();  
    lastSendTime = now;
  }
}
