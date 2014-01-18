#include <Wire.h>
#include "xadow.h"
 
#define SerialBaud   9600
#define Serial1Baud  9600

char buffer[5];
char lat[24];
char lon[36];

double pointLat = 3341.5618;
double pointLon = 11183.8117;

void setup()
{
  
  Serial.begin(SerialBaud);
  Serial1.begin(Serial1Baud);
  while(!Serial);
  Xadow.init();
  
  delay(1000);
}

char readChar(){
  int c = 0;
  do{
    c = Serial1.read();
  }
  while(c < 0);
  return c;
}


void loop()
{
 
      
      int v;
      int cnum;
      int latlen;
      int lonlen;
      Serial.println("Start");
      
      while (true){
        v = readChar();
        if (v == '$'){
          cnum = 0;
          latlen = lonlen = 0;
          Serial1.readBytes(buffer, 5);
          if (buffer[3] == 'M'){
            do {
              v = readChar();
              if(v == ','){
                cnum ++;
              }
              if(cnum == 3 & v != ','){
                  lat[latlen] = v ;// readChar();
                  latlen ++;
                  lat[latlen] = '\0';
              }
              if(cnum == 5 & v != ','){
                  lon[lonlen] = v ; //readChar();
                  lonlen ++;
                  lon[lonlen] = '\0';
              }
            } while( v != '*');
            Serial.println("lat");
            Serial.println(lat);
            Serial.println("Double lat");
            double dlat = atof(lat);
            Serial.println(dlat);

            Serial.println("Lon");
            Serial.println(lon);
            Serial.println("Double lon");
            double dlon = atof(lon);
            Serial.println(dlon);

            Serial.println("calculated lat");
            Serial.println( dlat - pointLat );
            Serial.println("calculated lon");
            Serial.println( dlon - pointLon );
          }
        }
      }
}
