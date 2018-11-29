/*------------------------------------------------------------------------------
  11/01/2016
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: webserver_rx_data.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how to send data to a webserver running
  on an ESP8266.
  https://youtu.be/EAUCajLvDKw
  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 
  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server;
char* ssid = "QueensLab";
char* password = "goteborg2021";
void setup()
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/toggle", toggleLED);
  server.on("/setcolor", setPixelColor);
  server.on("/reset", resetPixelColor);
  server.begin();
}
void loop()
{
  server.handleClient();
}
void toggleLED()
{
  digitalWrite(D1,!digitalRead(D1));
  digitalWrite(D2,!digitalRead(D2));
  digitalWrite(D3,!digitalRead(D3));
  
  server.send(200,"text/plain","Everything is reset");
}
void setPixelColor()
{
  String r = server.arg("red");
  String g = server.arg("grn");
  String b = server.arg("blu");
  
  analogWrite(D1, r.toInt());
  analogWrite(D2, g.toInt());
  analogWrite(D3, b.toInt());
  
  String rsp = r + ", " + g +  ", "  + b;
  server.send(200,"text/plain",rsp);
}
void resetPixelColor()
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  server.send(200,"text/plain","Everything is reset");
}