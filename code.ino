#include<DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22
#define BUTTON 1 //Acts as a Sensor
#define BUTTON 2 //Acts as a Sensor 2
//Initailiza Dht Sensor
DHT dht(DHTPIN,DHTTYPE); 


float humidity;
float temperature;

void setup() {
  
  Serial.begin(9600);
  //Start the dht 
  dht.begin();

}

void loop() {
  /*
   * First read the values of both temperature and humidity from the dht
   */
   temperature = dht.readTemperature();
   humidity = dht.readHumidity();
}
