

#include <sigma_delta.h>

#include<SPI.h>

#include<WiFi.h>

#define temps A0
#define baro A2
#define humid A1

 
String apiKey = "1QJ3GS4AESHJ4CX2";     

const char *ssid =  "Ricardo";     
const char *pass =  "emma2512";
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
      float tempValue = analogRead(temps) * 0.4887;
      float baroValue = map(analogRead(baro),0,1023,0,500);
      float humidValue = map(analogRead(humid),0,1023,0,100);
  
      

      if (client.connect(server,80))
      {  
                            
         String postStr = apiKey;
         postStr +="&field1=";
         postStr += String(tempValue);
         postStr +="&field2=";
         postStr += String(baroValue);
         postStr +="&field3=";
         postStr += String(humidValue);
         postStr += "\r\n\r\n";
 
         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr.length());
         client.print("\n\n");
         client.print(postStr);
 
         Serial.print("Temperature: ");
         Serial.print(tempValue);
         Serial.print(" degrees Celcius, Humidity: ");
         Serial.print(humidValue);
         Serial.print(" Pressure: ");
         Serial.print(baroValue);
         Serial.println("%. Send to Thingspeak.");
       }
       client.stop();
 
       Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
       delay(10000);
}
