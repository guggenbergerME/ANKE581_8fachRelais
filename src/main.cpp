#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h> 
#include <PubSubClient.h>   
#include <ArduinoOTA.h>

const byte relais_A = D7;       


// Kartendaten

const char* kartenID = "Relaiskarte_!";

WiFiClient espClient;
PubSubClient client(espClient);

// Connect to the WiFi
const char* ssid = "ANKE581";
const char* password = "q8d67nH5mH";
const char* mqtt_server = "192.168.1.3";


void callback(char* topic, byte* payload, unsigned int length) {

Serial.println("Callback - load");

payload[length] = '\0';

   Serial.print("payload: [");
   Serial.print((char *)payload);
   Serial.println("]");


    if (strcmp(topic,"Relais1/status")==0) {

        // Kanal A
        if ((char)payload[0] == 'o' && (char)payload[1] == 'n') {  
                 Serial.println("relais_A -> AN");
                 digitalWrite(relais_A, HIGH);
                 //client.publish("Relaiskarte/Weihnachten/24V_1","on");
                delay(100);
              }

        if ((char)payload[0] == 'o' && (char)payload[1] == 'f' && (char)payload[2] == 'f') {  
                 Serial.println("relais_A -> AUS");
                 digitalWrite(relais_A, LOW);
                 //client.publish("Relaiskarte/Weihnachten/24V_1","off");
                delay(100);
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
      client.subscribe("Relais1/status");
      //client.publish("Relais1", "off");
      client.publish("outTopic", "Online");

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

//Pins deklarieren
  pinMode(relais_A, OUTPUT);

// Alle Relais auf LOW setzen

  digitalWrite(relais_A, !LOW);

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


// Start mit Relais klack bestaetigen

digitalWrite(relais_A, LOW);
delay(300);
digitalWrite(relais_A, HIGH);
delay(300);
digitalWrite(relais_A, LOW);
delay(300);
digitalWrite(relais_A, HIGH);
delay(300);
digitalWrite(relais_A, LOW);



}


void loop() {

    // OTA Handle starten
  ArduinoOTA.handle(); 

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

delay(100);
  
}

