/*
*  ESP32 WiFi Auto Re-Connect
*  Full Tutorial @ https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/
*/
#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>
 
// Replace with your own network credentials
const char* ssid = SSID;
const char* password = PASS;

// monitor for voltage on GPIO34
const int potPin = 34;

// variable for storing the potentiometer value
int potValue = 0; 
 
void ConnectedToAP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Connected To The WiFi Network");
}
 
void GotIP_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}
 
void WiFi_Disconnected_Handler(WiFiEvent_t wifi_event, WiFiEventInfo_t wifi_info) {
  Serial.println("Disconnected From WiFi Network");
  // Attempt Re-Connection
  WiFi.begin(ssid, password);
}

char* signal_Speak_On() {
  char* msg = new char[16];
  strcpy(msg,"SPEAKER PLAYING");
  return msg;
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(ConnectedToAP_Handler, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(GotIP_Handler, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFi_Disconnected_Handler, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi Network ..");
}
 
void loop() {
  // Reading value
  potValue = analogRead(potPin);
  if (potValue > 4000) {
    Serial.println(signal_Speak_On());
  }
  else {
    Serial.print("GPIO34: ");
    Serial.println(potValue);
  }
  delay(500);
}
