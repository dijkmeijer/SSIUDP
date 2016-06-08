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

#define ip121

#ifdef IP121
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xAE };
IPAddress L_ip(172,16,29,121);
char ID_char[16]="ip121";
#endif
#ifdef IP122
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xA8 };
IPAddress L_ip(172,16,29,122);
char ID_char[16]="ip122";
#endif
#ifdef IP123
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xAA };
IPAddress L_ip(172,16,29,123);
char ID_char[16]="ip123";
#endif
#ifdef IP124
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xB2 };
IPAddress L_ip(172,16,29,124);
char ID_char[16]="ip124";
#endif
#ifdef IP125
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xB3 };
IPAddress L_ip(172,16,29,125);
char ID_char[16]="ip125";
#endif
#ifdef IP126
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xBA };
IPAddress L_ip(172,16,29,126);
char ID_char[16]="ip126";
#endif
#ifdef IP127
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xB9 };
IPAddress L_ip(172,16,29,127);
char ID_char[16]="ip127";
#endif
#ifdef IP128
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x44, 0xAC };
IPAddress L_ip(172,16,29,128);
char ID_char[16]="ip128";
#endif


byte R_ip[] = { 172,16,29,255 };


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


