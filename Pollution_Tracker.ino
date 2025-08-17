#include "WiFi_MQTT.h"
#include "AQI.h"
#include <DHT.h>
#include <LiquidCrystal.h>

DHT dht(DHTPIN, DHT11);

unsigned char deltaTime = 40;
float humidity = 0;
float carbonMonoxide = 0;
float dust = 0;
float calcVoltage = 0;
float dustDensity = 0;
float vZero = 0.2;
float vSlope = 0.91;
float coVolt = 0;
float coPPM = 0;
int coAQI = 0;
int pm25AQI = 0;
int overallAQI = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(DUSTLED, OUTPUT);
  pinMode(FLASHER, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  connectToWiFi();
  connectToMQTT();
  dht.begin();
  lcd.begin(16,2);
}

void loop() {
  delay(2000);
  lcd.setCursor(0, 0);
  
 
  humidity = dht.readHumidity();
  char humidityOut[20];
  sprintf(humidityOut, "%.2f", humidity);
  if (!mqttClient.connected()) 
  {
    lcd.print("MQTT not connected, \nattempting to reconnect...");
    connectToMQTT();  
  }
  mqttClient.publish(humidityTopic, humidityOut);
  lcd.clear();
  
  randomSeed(analogRead(0));
  carbonMonoxide = analogRead(COPIN);
  coVolt = carbonMonoxide * (5.0 / 1024.0);
  coPPM = abs((coVolt - vZero) / vSlope);
  //coPPM = 9 - (random(100, 701) / 1000.0);
  char coOut[20];
  sprintf(coOut, "%f", coPPM);
  if (!mqttClient.connected()) 
  {
    lcd.print("MQTT not connected, \nattempting to reconnect...");
    connectToMQTT();
  }
    
  mqttClient.publish(carbonmonoxideTopic, coOut);

  randomSeed(analogRead(0));
  digitalWrite(DUSTLED, LOW);
  dust = analogRead(DUSTPIN);
  delayMicroseconds(deltaTime);
  digitalWrite(DUSTLED, HIGH);
  calcVoltage = dust * (5.0 / 1024.0);
  dustDensity = abs(170 * calcVoltage - 0.1);
  dustDensity = 1000 * dustDensity - 60;
   //dust = random(0, 5001) / 1000.0; // Generates a random float between 0.0 and 5.0
   float dustDensity = 33 - dust;

  char dustOut[20];
  sprintf(dustOut, "%f", dustDensity);
  if (!mqttClient.connected()) 
  {
    lcd.print("MQTT not connected, \nattempting to reconnect...");
    connectToMQTT();
  }
  mqttClient.publish(dustTopic, dustOut);
  
  coAQI = calculateCOAQI(coPPM);
  pm25AQI = calculatePM25AQI(dustDensity);
  overallAQI = max(coAQI, pm25AQI);
  char AQIOut[20];
  sprintf(AQIOut, "%d", overallAQI);
  if (!mqttClient.connected()) 
  {
    lcd.print("MQTT not connected,\n attempting to reconnect...");
    connectToMQTT();  
  }
  mqttClient.publish(AQITopic, AQIOut);
  lcd.clear();

  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(3000);
  lcd.clear();
  
  lcd.print("CO: ");
  lcd.print(coPPM);
  lcd.print(" ppm");
  delay(3000);
  lcd.clear();

  lcd.print("Dust: ");
  lcd.print(dustDensity);
  lcd.print(" ug/m^3");
  delay(3000);
  lcd.clear();

  lcd.print("AQI: ");
  lcd.print(overallAQI);
  delay(3000);
  lcd.clear();

  if((coPPM > 9.3))
  {
    lcd.print("Warning, CO Level is High");
    digitalWrite(BUZZERPIN, HIGH);
    delay(5000);
  }
  digitalWrite(BUZZERPIN, LOW);
  lcd.clear();
  int i = 0;
  if (dustDensity > 35)
  {
    while(i<20)
    {
      digitalWrite(FLASHER, !digitalRead(FLASHER));
      lcd.print("Warning, High Dust Density");
      delay(150);
      i++;
    }
  }
  lcd.clear();
  mqttClient.loop();
  delay(2000);
}
