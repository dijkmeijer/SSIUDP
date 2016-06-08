/*
  Web  Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 4 Sep 2010
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include <EthernetUdp.h>
#include <stdio.h>
#include <SSI.h>




// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xAE };
//byte L_ip[] = { 172,16,29,121 };
//byte R_ip[] = { 172,16,29,255 };
IPAddress L_ip(10,0,0, 177);
IPAddress R_IP(10,0,0, 11);
char ID_char[16]="ip121";
int interval;
int port=21992;
int restart;
char S1[32];
SSI encoder;
String line;
char c;
byte b;
int pos;


EthernetUDP Udp;

void setup()
{
   Serial.begin(9600);
   Serial.println("startup");
   Ethernet.begin(mac, L_ip);
   Udp.begin(21990);
   encoder.setdirection(1);
   zero(); 
}

void loop()
{
  // listen for incoming clients

   delay(interval);
   if(Serial.available() > 0) {
      c=Serial.read();
      switch(c) {
        case 'l': encoder.setdirection(0); break;
        case 'r': encoder.setdirection(1); break;
        case 'n': zero(); Serial.println("nul"); break;
      }
   }
   encoder.getPosition();
   encoder.condensePosition();
   pos=(int)encoder.position;
   sprintf(S1,"%4d%s",pos, ID_char);
   Udp.beginPacket(R_IP, port);
   Udp.write(S1);
   Udp.endPacket();
   Serial.println(S1);
   if(pos > 4000) zero();
  
   delay(10);
                    
}


void zero() {
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
  delay(100);
  digitalWrite(A5, HIGH);
  pinMode(A5, INPUT);
}


