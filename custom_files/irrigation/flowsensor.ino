/*
  YF‐G1 Water Flow Sensor
  Water Flow Sensor output processed to read in litres/hour
  By Sander Rozemuller 
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "settings.h"

volatile int flow_frequency; // Measures flow sensor pulses
// Calculated litres/hour
float vol = 0.0, l_minute, currentVolume;
unsigned char flowsensor = 4; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
int mqttDelayCounter = 0; // count in the loop till this value is reached. Then it will send the value to MQTT. Flood prevention
void flow () // Interrupt function
{
  flow_frequency++;
}
WiFiClient espClient;
PubSubClient client(espClient);


void setup()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // Blink the LED until we're connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  // Connect to MQTT
  client.setServer(mqtt_server, 1883);
  // Initiate the sensor

  delay(50);

  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  Serial.print("Water Flow Meter");
  Serial.print("Circuit Digest");
  currentTime = millis();
  cloopTime = currentTime;
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    digitalWrite(0, HIGH);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("FlowSensor", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      digitalWrite(0, LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop ()
{
  if (!client.connected()) {
    reconnect();
  }
  // Let MQTT do it's thing
  client.loop();
  currentTime = millis();
//  mqttSend = false;

  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
      mqttDelayCounter++;
      Serial.print("delaycounter:");
    Serial.println(mqttDelayCounter);
    cloopTime = currentTime; // Updates cloopTime

    if (flow_frequency != 0) {
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 4.8); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      Serial.print("Rate: ");
      Serial.print(l_minute);
      Serial.print(" L/M");
      l_minute = l_minute / 60;
      vol = vol + l_minute;
      currentVolume = currentVolume + l_minute ;
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.print(" L");
      flow_frequency = 0; // Reset Counter
      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");
      Serial.print("currentVolume:");
      Serial.println(currentVolume);
      // Every 60 seconds, send value to MQTT
      if (mqttDelayCounter == 60 )
      {
        Serial.print("Send to MQTT ");
        Serial.print(mqttDelayCounter);
       Serial.println("set counter back to 0");
       mqttDelayCounter = 0;
        client.publish(mqtt_pub_topic_total_liters, String(vol).c_str(), true);
        client.publish(mqtt_pub_topic_flowrate, String(l_minute).c_str(), true);
        client.publish(mqtt_pub_topic_current_liters, String(currentVolume).c_str(), true);
        client.publish(mqtt_pub_topic_pump_status, String("Running").c_str(), true);
      }
    }
    else {
      Serial.println(" flow rate = 0 ");
      Serial.print("Rate: ");
      Serial.print( flow_frequency );
      Serial.print(" L/M");
      Serial.print("Vol:");
      Serial.print(vol);
      Serial.print(" L");
            Serial.print("current:");
      Serial.print(currentVolume);
      if (mqttDelayCounter == 60 )
      {
        Serial.print("Send to MQTT ");
        Serial.print(mqttDelayCounter);
       Serial.println("set counter back to 0");
       mqttDelayCounter = 0;
        client.publish(mqtt_pub_topic_total_liters, String(vol).c_str(), true);
        client.publish(mqtt_pub_topic_flowrate, String(l_minute).c_str(), true);
        client.publish(mqtt_pub_topic_current_liters, String(currentVolume).c_str(), true);
        client.publish(mqtt_pub_topic_pump_status, String("Stopped").c_str(), true);
        currentVolume = 0; // when flow is stopped.. first send last value then reset.
      }
    }
  }
}