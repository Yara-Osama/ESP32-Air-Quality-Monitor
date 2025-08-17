#ifndef _WIFI_MQTT_h
#define _WIFI_MQTT_h

#include <LiquidCrystal.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define DHTPIN     4
#define COPIN      27
#define DUSTPIN    25
#define DUSTLED    33
#define BUZZERPIN  32
#define FLASHER    26

extern const char* mqttServer;
extern const char* humidityTopic;
extern const char* carbonmonoxideTopic;
extern const char* dustTopic;
extern const char* AQITopic;
extern const int   mqttPort;

extern LiquidCrystal lcd;


extern WiFiClient espClient;
extern PubSubClient mqttClient;

void connectToWiFi();
void connectToMQTT();
void reconnect();

#endif 
