#include <ESP8266WiFi.h>
String apiKey = "N4B71Z83G4B7VBYN";
const char *ssid = "Redmi"; 
const char *pass = "ayush123";
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup()
{
Serial.begin(115200);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
float h = analogRead(A0);
if (isnan(h))
{
Serial.println("Failed to read from MQ-2 sensor!");
return;
}
float w = analogRead(D1);
if(isnan(w))
{
  Serial.println("Failed to read from MQ-7 sensor!");
  return;
}
float q = analogRead(D2);
if(isnan(q))
{
  Serial.println("Failed to read from MQ-135 sensor!");
  return;
}
if (client.connect(server, 80)) 
{
String postStr = apiKey;
postStr += "&field1=";
postStr += String(h/1023*100);
postStr += "&field2=";
postStr += String(w/1023*100);
postStr += "&field3=";
postStr += String(q/1023*100);
postStr += "r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
Serial.print("MQ 2 level ");
Serial.println(h/1023*100);
Serial.print("MQ 7 level ");
Serial.println(w/1023*100);
Serial.print("MQ-135 level ");
Serial.println(q/1023*100);
Serial.println("Data Send to Thingspeak");
}
client.stop();
Serial.println("Waiting...");

delay(1500);
}
