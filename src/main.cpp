#include <Arduino.h>
#include <SPI.h>
#include "PCF8574.h"
#include <ESP8266WiFi.h> 
#include <PubSubClient.h>  
#include <OneWire.h>

/////////////////////////////////////////////////////////////////////////// PCF8574 Adresse
PCF8574 pcf8574(0x20);
//PCF8574 pcf8574_2(0x21);
/*
PINOUT Wemos Expander
D1 SCL
D2 SDA
Pinout -> https://bre.is/9H5nddhG
*/

/////////////////////////////////////////////////////////////////////////// Schleifen verwalten
unsigned long previousMillis_mqttCHECK = 0; // mqtt Abfragen
unsigned long interval_mqttCHECK = 500; 


/////////////////////////////////////////////////////////////////////////// Variablen
int mqtt_variablen_einmalig_anlegen = 0;


/////////////////////////////////////////////////////////////////////////// Kartendaten

const char* kartenID = "Relaiskarte_!";

WiFiClient espClient;
PubSubClient client(espClient);

// Connect to the WiFi
const char* ssid = "ANKE581";
const char* password = "q8d67nH5mH";
const char* mqtt_server = "192.168.1.3";

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
void loop                       ();
void callback                   (char* topic, byte* payload, unsigned int length);
void reconnect                  ();
void setuo                      ();
void mqtt_connected             ();


void callback(char* topic, byte* payload, unsigned int length) {

/*
Serial.println("Callback - load");
payload[length] = '\0';
   Serial.print("payload: [");
   Serial.print((char *)payload);
   Serial.println("]");
*/

    if (strcmp(topic,"ANKE581/RK001/IN/Relais/A")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_A -> AN");
                 pcf8574.digitalWrite(P0, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_A -> AUS");
                 pcf8574.digitalWrite(P0, !LOW);

              }
      } 


    if (strcmp(topic,"ANKE581/RK001/IN/Relais/B")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_B -> AN");
                 pcf8574.digitalWrite(P1, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_B -> AUS");
                 pcf8574.digitalWrite(P1, !LOW);
              }
      } 

    if (strcmp(topic,"ANKE581/RK001/IN/Relais/C")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_C -> AN");
                 pcf8574.digitalWrite(P2, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_C -> AUS");
                 pcf8574.digitalWrite(P2, !LOW);
              }
      } 

    if (strcmp(topic,"ANKE581/RK001/IN/Relais/D")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_D -> AN");
                 pcf8574.digitalWrite(P3, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_D -> AUS");
                 pcf8574.digitalWrite(P3, !LOW);
              }
      } 


    if (strcmp(topic,"ANKE581/RK001/IN/Relais/E")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_E -> AN");
                 pcf8574.digitalWrite(P4, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_E -> AUS");
                 pcf8574.digitalWrite(P4, !LOW);
              }
      } 

    if (strcmp(topic,"ANKE581/RK001/IN/Relais/F")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_F -> AN");
                 pcf8574.digitalWrite(P5, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_F -> AUS");
                 pcf8574.digitalWrite(P5, !LOW);
              }
      } 


    if (strcmp(topic,"ANKE581/RK001/IN/Relais/G")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_G -> AN");
                 pcf8574.digitalWrite(P6, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_G -> AUS");
                 pcf8574.digitalWrite(P6, !LOW);
              }
      } 

    if (strcmp(topic,"ANKE581/RK001/IN/Relais/H")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_H -> AN");
                 pcf8574.digitalWrite(P7, !HIGH);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_H -> AUS");
                 pcf8574.digitalWrite(P7, !LOW);
              }
      } 


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Baue Verbindung zum mqtt Server auf. IP: ");
    // Attempt to connect
    if (client.connect(kartenID,"anke581","Sa,7+CGPfA9e6)y!")) {
      //Serial.println("connected");
      ////////////////////////////////////////////////////////////////////////// SUBSCRIBE Eintraege
        client.subscribe("ANKE581/RK001/IN/Relais/A");
        client.publish("ANKE581/RK001/IN/Relais/A", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/B");
        client.publish("ANKE581/RK001/IN/Relais/B", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/C");
        client.publish("ANKE581/RK001/IN/Relais/C", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/D");
        client.publish("ANKE581/RK001/IN/Relais/D", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/E");
        client.publish("ANKE581/RK001/IN/Relais/E", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/F");
        client.publish("ANKE581/RK001/IN/Relais/F", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/G");
        client.publish("ANKE581/RK001/IN/Relais/G", "Online"); // mqtt Bekanntgabe

        client.subscribe("ANKE581/RK001/IN/Relais/H");
        client.publish("ANKE581/RK001/IN/Relais/H", "Online"); // mqtt Bekanntgabe                                                
      
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {

/////////////////////////////////////////////////////////////////////////// Konfig Relais
  pcf8574.pinMode(P0, OUTPUT);
  pcf8574.pinMode(P1, OUTPUT);
  pcf8574.pinMode(P2, OUTPUT);
  pcf8574.pinMode(P3, OUTPUT);
  pcf8574.pinMode(P4, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
  pcf8574.pinMode(P6, OUTPUT);
  pcf8574.pinMode(P7, OUTPUT);        
  pcf8574.begin();
/////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////// Relais OFF
pcf8574.digitalWrite(P0, !LOW);
pcf8574.digitalWrite(P1, !LOW);
pcf8574.digitalWrite(P2, !LOW);
pcf8574.digitalWrite(P3, !LOW);
pcf8574.digitalWrite(P4, !LOW);
pcf8574.digitalWrite(P5, !LOW);
pcf8574.digitalWrite(P6, !LOW);
pcf8574.digitalWrite(P7, !LOW);
/////////////////////////////////////////////////////////////////////////// 

// MQTT Broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

// Serielle Kommunikation starten
  Serial.begin(115200);

  // WiFi 
  IPAddress ip(192, 168, 1, 20);
	IPAddress dns(192, 168, 1, 1);  
	IPAddress subnet(255, 255, 0, 0);
	IPAddress gateway(192, 168, 1, 1);
	WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(ssid, password);

  // Wifi AP deaktivieren
  WiFi.mode(WIFI_STA);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi connected...");


}

/////////////////////////////////////////////////////////////////////////// mqtt connected
void mqtt_connected(){

     // mqtt Daten senden     
  if (!client.connected()) {
      reconnect();
    }
    client.loop(); 

}

/////////////////////////////////////////////////////////////////////////// mqtt einmalig anlegen
void mqtt_einmalig_anlegen(){

 if (mqtt_variablen_einmalig_anlegen == 0) {
  
  // mqtt Publish
  client.publish("ANKE581/RK001/IN/Relais/A", "off");
  Serial.print("mqtt gesendet ...");
  mqtt_variablen_einmalig_anlegen = 1;
 }

}


void loop() {

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ mqtt Checken
  if (millis() - previousMillis_mqttCHECK > interval_mqttCHECK) {
      previousMillis_mqttCHECK = millis(); 
      mqtt_connected();
    }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ mqtt Variablen für IO Broker einmalig anlegen
 mqtt_einmalig_anlegen();

  
}

