#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

struct _locData {
  unsigned short year;
  unsigned char month;
  unsigned char day;
  unsigned char hour;
  unsigned char minute;
  unsigned char second;
  unsigned char fixType;
  long lon;
  long lat;
  unsigned char numSV;
  unsigned long hAcc;
  long gSpeed;
  long heading;
};

void setup() 
{ 
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("Init failed");
  else
    Serial.println("Init succeeded");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    rf95.setFrequency(433.64);
    rf95.setModemConfig(RH_RF95::Bw125Cr48Sf4096);

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
//  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true. 
  // Failure to do that will result in extremely low transmit powers.
//  driver.setTxPower(14, true);
}

void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now   
    uint8_t data[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(data);
    if (rf95.recv(data, &len))
    {
      if ( len == sizeof(_locData) ) {
        _locData* loc = (_locData*)data;
        char buf[64];
        sprintf(buf, "%d %d %d/%d/%d %d:%d:%d %ld %ld", loc->fixType, loc->numSV, loc->year, loc->month, loc->day, loc->hour, loc->minute, loc->second, loc->lat, loc->lon);
        Serial.println(buf);
      }
      else {
        Serial.print("Text: ");
        Serial.println((char*)data);
      }
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.print("SNR: ");
      Serial.println(rf95.lastSNR(), DEC);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}


